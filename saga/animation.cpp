/* ScummVM - Scumm Interpreter
 * Copyright (C) 2004 The ScummVM project
 *
 * The ReInherit Engine is (C)2000-2003 by Daniel Balsom.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * $Header$
 *
 */

// Background animation management module
#include "saga.h"
#include "gfx_mod.h"

#include "cvar_mod.h"
#include "console_mod.h"
#include "game_mod.h"
#include "events_mod.h"
#include "render.h"

#include "animation.h"

namespace Saga {

static void CF_anim_info(int argc, char *argv[], void *refCon);

int Anim::reg() {
	CVAR_RegisterFunc(CF_anim_info, "anim_info", NULL, R_CVAR_NONE, 0, 0, this);
	return R_SUCCESS;
}

Anim::Anim(void) {
	int i;

	_anim_limit = R_MAX_ANIMATIONS;
	_anim_count = 0;

	for (i = 0; i < R_MAX_ANIMATIONS; i++)
		_anim_tbl[i] = NULL;

	_initialized = true;
}

Anim::~Anim(void) {
	uint16 i;

	for (i = 0; i < R_MAX_ANIMATIONS; i++) {
		if (_anim_tbl[i])
			free(_anim_tbl[i]);
	}

	_initialized = false;
}

int Anim::load(const byte *anim_resdata, size_t anim_resdata_len, uint16 *anim_id_p) {
	R_ANIMATION *new_anim;

	uint16 anim_id = 0;
	uint16 i;

	if (!_initialized) {
		warning("Anim::load not initialised");
		return R_FAILURE;
	}

	// Find an unused animation slot
	for (i = 0; i < R_MAX_ANIMATIONS; i++) {
		if (_anim_tbl[i] == NULL) {
			anim_id = i;
			break;
		}
	}

	if (i == R_MAX_ANIMATIONS) {
		warning("Anim::load could not find unused animation slot");
		return R_FAILURE;
	}

	new_anim = (R_ANIMATION *)malloc(sizeof *new_anim);
	if (new_anim == NULL) {
		warning("Anim::load Allocation failure");
		return R_MEM;
	}

	new_anim->resdata = anim_resdata;
	new_anim->resdata_len = anim_resdata_len;

	if (GAME_GetGameType() == R_GAMETYPE_ITE) {
		if (getNumFrames(anim_resdata, anim_resdata_len, &new_anim->n_frames) != R_SUCCESS) {
			warning("Anim::load Couldn't get animation frame count");
			return R_FAILURE;
		}

		// Cache frame offsets
		new_anim->frame_offsets = (size_t *)malloc(new_anim->n_frames * sizeof *new_anim->frame_offsets);
		if (new_anim->frame_offsets == NULL) {
			warning("Anim::load Allocation failure");
			return R_MEM;
		}

		for (i = 0; i < new_anim->n_frames; i++) {
			getFrameOffset(anim_resdata, anim_resdata_len, i + 1, &new_anim->frame_offsets[i]);
		}
	} else {
		new_anim->cur_frame_p = anim_resdata + SAGA_FRAME_HEADER_LEN;
		new_anim->cur_frame_len = anim_resdata_len - SAGA_FRAME_HEADER_LEN;
		getNumFrames(anim_resdata, anim_resdata_len, &new_anim->n_frames);
	}

	// Set animation data
	new_anim->current_frame = 1;
	new_anim->end_frame = new_anim->n_frames;
	new_anim->stop_frame = new_anim->end_frame;

	new_anim->frame_time = R_DEFAULT_FRAME_TIME;
	new_anim->flags = 0;
	new_anim->play_flag = 0;
	new_anim->link_flag = 0;
	new_anim->link_id = 0;

	_anim_tbl[anim_id] = new_anim;

	*anim_id_p = anim_id;

	_anim_count++;

	return R_SUCCESS;
}

int Anim::link(uint16 anim_id1, uint16 anim_id2) {
	R_ANIMATION *anim1;
	R_ANIMATION *anim2;

	if ((anim_id1 >= _anim_count) || (anim_id2 >= _anim_count)) {
		return R_FAILURE;
	}

	anim1 = _anim_tbl[anim_id1];
	anim2 = _anim_tbl[anim_id2];

	if ((anim1 == NULL) || (anim2 == NULL)) {
		return R_FAILURE;
	}

	anim1->link_id = anim_id2;
	anim1->link_flag = 1;

	anim2->frame_time = anim1->frame_time;

	return R_SUCCESS;
}

int Anim::play(uint16 anim_id, int vector_time) {
	R_EVENT event;
	R_ANIMATION *anim;
	R_ANIMATION *link_anim;
	uint16 link_anim_id;

	R_BUFFER_INFO buf_info;

	byte *display_buf;

	const byte *nextf_p;
	size_t nextf_len;

	uint16 frame;
	int result;

	R_GAME_DISPLAYINFO disp_info;

	if (anim_id >= _anim_count) {
		return R_FAILURE;
	}

	GAME_GetDisplayInfo(&disp_info);

	_vm->_render->getBufferInfo(&buf_info);
	display_buf = buf_info.r_bg_buf;

	anim = _anim_tbl[anim_id];
	if (anim == NULL) {
		return R_FAILURE;
	}

	if (anim->play_flag) {
		frame = anim->current_frame;
		if (GAME_GetGameType() == R_GAMETYPE_ITE) {
			result = ITE_DecodeFrame(anim->resdata, anim->resdata_len, anim->frame_offsets[frame - 1], display_buf,
									disp_info.logical_w * disp_info.logical_h);
			if (result != R_SUCCESS) {
				warning("ANIM::play: Error decoding frame %u", anim->current_frame);
				anim->play_flag = 0;
				return R_FAILURE;
			}
		} else {
			if (anim->cur_frame_p == NULL) {
				warning("ANIM::play: Frames exhausted");
				return R_FAILURE;
			}

			result = IHNM_DecodeFrame(display_buf,  disp_info.logical_w * disp_info.logical_h,
									anim->cur_frame_p, anim->cur_frame_len, &nextf_p, &nextf_len);
			if (result != R_SUCCESS) {
				warning("ANIM::play: Error decoding frame %u", anim->current_frame);
				anim->play_flag = 0;
				return R_FAILURE;
			}

			anim->cur_frame_p = nextf_p;
			anim->cur_frame_len = nextf_len;
		}
		anim->current_frame++;
	}

	anim->play_flag = 1;

	if (anim->current_frame > anim->n_frames) {
		// Animation done playing
		if (anim->link_flag) {
			// If this animation has a link, follow it
			anim->play_flag = 0;
			anim->current_frame = 1;

			link_anim_id = anim->link_id;
			link_anim = _anim_tbl[link_anim_id];

			if (link_anim != NULL) {
				link_anim->current_frame = 1;
				link_anim->play_flag = 1;
			}

			anim_id = link_anim_id;
		} else if (anim->flags & ANIM_LOOP) {
			// Loop animation
			anim->current_frame = 1;
			anim->cur_frame_p = anim->resdata + SAGA_FRAME_HEADER_LEN;
			anim->cur_frame_len = anim->resdata_len - SAGA_FRAME_HEADER_LEN;
		} else {
			// No link, stop playing
			anim->current_frame = anim->n_frames;
			anim->play_flag = 0;

			if (anim->flags & ANIM_ENDSCENE) {
				// This animation ends the scene
				event.type = R_ONESHOT_EVENT;
				event.code = R_SCENE_EVENT;
				event.op = EVENT_END;
				event.time = anim->frame_time + vector_time;
				EVENT_Queue(&event);
			}
			return R_SUCCESS;
		}
	}

	event.type = R_ONESHOT_EVENT;
	event.code = R_ANIM_EVENT;
	event.op = EVENT_FRAME;
	event.param = anim_id;
	event.time = anim->frame_time + vector_time;

	EVENT_Queue(&event);

	return R_SUCCESS;
}

int Anim::reset() {
	uint16 i;

	for (i = 0; i < R_MAX_ANIMATIONS; i++) {

		freeId(i);
	}

	_anim_count = 0;

	return R_SUCCESS;
}

int Anim::setFlag(uint16 anim_id, uint16 flag) {
	R_ANIMATION *anim;

	if (anim_id > _anim_count) {
		return R_FAILURE;
	}

	anim = _anim_tbl[anim_id];
	if (anim == NULL) {
		return R_FAILURE;
	}

	anim->flags |= flag;

	return R_SUCCESS;
}

int Anim::setFrameTime(uint16 anim_id, int time) {
	R_ANIMATION *anim;

	if (anim_id > _anim_count) {
		return R_FAILURE;
	}

	anim = _anim_tbl[anim_id];
	if (anim == NULL) {
		return R_FAILURE;
	}

	anim->frame_time = time;

	return R_SUCCESS;
}

int Anim::freeId(uint16 anim_id) {
	R_ANIMATION *anim;

	if (anim_id > _anim_count) {
		return R_FAILURE;
	}

	anim = _anim_tbl[anim_id];
	if (anim == NULL) {
		return R_FAILURE;
	}

	if (GAME_GetGameType() == R_GAMETYPE_ITE) {
		free(anim->frame_offsets);
		anim->frame_offsets = NULL;
	}

	free(anim);
	_anim_tbl[anim_id] = NULL;
	_anim_count--;

	return R_SUCCESS;
}

// The actual number of frames present in an animation resource is 
// sometimes less than number present in the .nframes member of the
// animation header. For this reason, the function attempts to find
// the last valid frame number, which it returns via 'n_frames'
int Anim::getNumFrames(const byte *anim_resource, size_t anim_resource_len, uint16 *n_frames) {
	R_ANIMATION_HEADER ah;

	size_t offset;
	int magic;

	int x;

	if (!_initialized) {
		return R_FAILURE;
	}

	MemoryReadStream *readS = new MemoryReadStream(anim_resource, anim_resource_len);

	ah.magic = readS->readUint16LE();
	ah.screen_w = readS->readUint16LE();
	ah.screen_h = readS->readUint16LE();

	ah.unknown06 = readS->readByte();
	ah.unknown07 = readS->readByte();
	ah.nframes = readS->readByte();

	if (GAME_GetGameType() == R_GAMETYPE_IHNM) {
		*n_frames = ah.nframes;
	}

	if (ah.magic == 68) {
		for (x = ah.nframes; x > 0; x--) {
			if (getFrameOffset(anim_resource, anim_resource_len, x, &offset) != R_SUCCESS) {
				return R_FAILURE;
			}

			magic = *(anim_resource + offset);
			if (magic == SAGA_FRAME_HEADER_MAGIC) {
				*n_frames = x;
				return R_SUCCESS;
			}
		}

		return R_FAILURE;
	}

	return R_FAILURE;
}

int Anim::ITE_DecodeFrame(const byte *resdata, size_t resdata_len, size_t frame_offset, byte *buf, size_t buf_len) {
	R_ANIMATION_HEADER ah;
	R_FRAME_HEADER fh;

	byte *write_p;

	uint16 magic;

	uint16 x_start;
	uint16 y_start;
	uint32 screen_w;
	uint32 screen_h;

	int mark_byte;
	byte data_byte;
	int new_row;

	uint16 control_ch;
	uint16 param_ch;

	uint16 runcount;
	int x_vector;

	uint16 i;

	if (!_initialized) {
		return R_FAILURE;
	}

	MemoryReadStream *readS = new MemoryReadStream(resdata, resdata_len);
	// Read animation header
	ah.magic = readS->readUint16LE();
	ah.screen_w = readS->readUint16LE();
	ah.screen_h = readS->readUint16LE();
	ah.unknown06 = readS->readByte();
	ah.unknown07 = readS->readByte();
	ah.nframes = readS->readByte();
	ah.flags = readS->readByte();
	ah.unknown10 = readS->readByte();
	ah.unknown11 = readS->readByte();

	screen_w = ah.screen_w;
	screen_h = ah.screen_h;

	if ((screen_w * screen_h) > buf_len) {
		// Buffer argument is too small to hold decoded frame, abort.
		warning("ITE_DecodeFrame: Buffer size inadequate");
		return R_FAILURE;
	}

	// Read frame header
	readS = new MemoryReadStream(resdata + frame_offset, resdata_len - frame_offset);

	// Check for frame magic byte
	magic = readS->readByte();
	if (magic != SAGA_FRAME_HEADER_MAGIC) {
		warning("ITE_DecodeFrame: Invalid frame offset");
		return R_FAILURE;
	}

	// For some strange reason, the animation header is in little 
	// endian format, but the actual RLE encoded frame data, 
	// including the frame header, is in big endian format.

	fh.x_start = readS->readUint16BE();
	fh.y_start = readS->readByte();
	readS->readByte();		/* Skip pad byte */
	fh.x_pos = readS->readUint16BE();
	fh.y_pos = readS->readUint16BE();
	fh.width = readS->readUint16BE();
	fh.height = readS->readUint16BE();

	x_start = fh.x_start;
	y_start = fh.y_start;

	// Setup write pointer to the draw origin
	write_p = (buf + (y_start * screen_w) + x_start);

	// Begin RLE decompression to output buffer
	do {
		mark_byte = readS->readByte();
		switch (mark_byte) {
		case 0x10: // Long Unencoded Run
			runcount = readS->readSint16BE();
			for (i = 0; i < runcount; i++) {
				data_byte = readS->readByte();
				if (data_byte != 0) {
					*write_p = data_byte;
				}
				write_p++;
			}
			continue;
			break;
		case 0x20: // Long encoded run
			runcount = readS->readSint16BE();
			data_byte = readS->readByte();
			for (i = 0; i < runcount; i++) {
				*write_p++ = data_byte;
			}
			continue;
			break;
		case 0x2F: // End of row
			x_vector = readS->readSint16BE();
			new_row = readS->readByte();
			// Set write pointer to the new draw origin
			write_p = buf + ((y_start + new_row) * screen_w) + x_start + x_vector;
			continue;
			break;
		case 0x30: // Reposition command
			x_vector = readS->readSint16BE();
			write_p += x_vector;
			continue;
			break;
		case 0x3F: // End of frame marker
			return R_SUCCESS;
			break;
		default:
			break;
		}

		// Mask all but two high order control bits
		control_ch = mark_byte & 0xC0U;
		param_ch = mark_byte & 0x3FU;
		switch (control_ch) {
		case 0xC0: // 1100 0000
			// Run of empty pixels
			runcount = param_ch + 1;
			write_p += runcount;
			continue;
			break;
		case 0x80: // 1000 0000
			// Run of compressed data
			runcount = param_ch + 1;
			data_byte = readS->readByte();
			for (i = 0; i < runcount; i++) {
				*write_p++ = data_byte;
			}
			continue;
			break;
		case 0x40: // 0100 0000
			// Uncompressed run
			runcount = param_ch + 1;
			for (i = 0; i < runcount; i++) {
				data_byte = readS->readByte();
				if (data_byte != 0) {
					*write_p = data_byte;
				}
				write_p++;
			}
			continue;
			break;
		default:
			// Unknown marker found - abort
			warning("ITE_DecodeFrame: Invalid RLE marker encountered");
			return R_FAILURE;
			break;
		}
	} while (mark_byte != 63); // end of frame marker

	return R_SUCCESS;
}

int Anim::IHNM_DecodeFrame(byte *decode_buf, size_t decode_buf_len, const byte *thisf_p,
					size_t thisf_len, const byte **nextf_p, size_t *nextf_len) {
	int in_ch;
	int decoded_data = 0;
	int cont_flag = 1;
	int control_ch;
	int param_ch;
	byte data_pixel;
	int x_origin = 0;
	int y_origin = 0;
	int x_vector;
	int new_row;

	uint16 runcount;
	uint16 c;

	size_t in_ch_offset;

	MemoryReadStream *readS = new MemoryReadStream(thisf_p, thisf_len);

	byte *outbuf_p = decode_buf;
	byte *outbuf_endp = (decode_buf + decode_buf_len) - 1;
	size_t outbuf_remain = decode_buf_len;

	R_GAME_DISPLAYINFO di;

	GAME_GetDisplayInfo(&di);

	*nextf_p = NULL;

	for (; cont_flag; decoded_data = 1) {
		in_ch_offset = readS->pos();
		in_ch = readS->readByte();
		switch (in_ch) {
		case 0x0F: // 15: Frame header
			{
				int param1;
				int param2;
				int param3;
				int param4;
				int param5;
				int param6;

				if (thisf_len - readS->pos() < 13) {
					warning("0x%02X: Input buffer underrun", in_ch);
					return R_FAILURE;
				}

				param1 = readS->readUint16BE();
				param2 = readS->readUint16BE();
				readS->readByte(); // skip 1?
				param3 = readS->readUint16BE();
				param4 = readS->readUint16BE();
				param5 = readS->readUint16BE();
				param6 = readS->readUint16BE();

				x_origin = param1;
				y_origin = param2;

				outbuf_p = decode_buf + x_origin + (y_origin * di.logical_w);

				if (outbuf_p > outbuf_endp) {
					warning("0x%02X: (0x%X) Invalid output position. (x: %d, y: %d)",
							in_ch, in_ch_offset, x_origin, y_origin);
					return R_FAILURE;
				}

				outbuf_remain = (outbuf_endp - outbuf_p) + 1;
				continue;
			}
			break;
		case 0x10: // Long Unencoded Run
			runcount = readS->readSint16BE();
			if (thisf_len - readS->pos() < runcount) {
				warning("0x%02X: Input buffer underrun", in_ch);
				return R_FAILURE;
			}
			if (outbuf_remain < runcount) {
				warning("0x%02X: Output buffer overrun", in_ch);
				return R_FAILURE;
			}

			for (c = 0; c < runcount; c++) {
				data_pixel = readS->readByte();
				if (data_pixel != 0) {
					*outbuf_p = data_pixel;
				}
				outbuf_p++;
			}

			outbuf_remain -= runcount;
			continue;
			break;
		case 0x1F: // 31: Unusued?
			if (thisf_len - readS->pos() < 3) {
				warning("0x%02X: Input buffer underrun", in_ch);
				return R_FAILURE;
			}

			readS->readByte();
			readS->readByte();
			readS->readByte();
			continue;
			break;
		case 0x20: // Long compressed run
			if (thisf_len - readS->pos() <= 3) {
				warning("0x%02X: Input buffer underrun", in_ch);
				return R_FAILURE;
			}

			runcount = readS->readSint16BE();
			data_pixel = readS->readByte();

			for (c = 0; c < runcount; c++) {
				*outbuf_p++ = data_pixel;
			}

			outbuf_remain -= runcount;
			continue;
			break;

		case 0x2F: // End of row
			if (thisf_len - readS->pos() <= 4) {
				return R_FAILURE;
			}

			x_vector = readS->readSint16BE();
			new_row = readS->readSint16BE();

			outbuf_p = decode_buf + ((y_origin + new_row) * di.logical_w) + x_origin + x_vector;
			outbuf_remain = (outbuf_endp - outbuf_p) + 1;
			continue;
			break;
		case 0x30: // Reposition command
			if (thisf_len - readS->pos() < 2) {
				return R_FAILURE;
			}

			x_vector = readS->readSint16BE();

			if (((x_vector > 0) && ((size_t) x_vector > outbuf_remain)) || (-x_vector > outbuf_p - decode_buf)) {
				warning("0x30: Invalid x_vector");
				return R_FAILURE;
			}

			outbuf_p += x_vector;
			outbuf_remain -= x_vector;
			continue;
			break;

		case 0x3F:	// 68: Frame end marker
			debug(1, "0x3F: Frame end marker");
			if (decoded_data && (thisf_len - readS->pos() > 0)) {
				*nextf_p = thisf_p + readS->pos();
				*nextf_len = thisf_len - readS->pos();
			} else {
				*nextf_p = NULL;
				*nextf_len = 0;
			}

			cont_flag = 0;
			continue;
			break;

		default:
			break;
		}

		control_ch = in_ch & 0xC0;
		param_ch = in_ch & 0x3f;
		switch (control_ch) {

		case 0xC0: // Run of empty pixels
			runcount = param_ch + 1;
			if (outbuf_remain < runcount) {
				return R_FAILURE;
			}

			outbuf_p += runcount;
			outbuf_remain -= runcount;
			continue;
			break;
		case 0x80: // Run of compressed data
			runcount = param_ch + 1;
			if ((outbuf_remain < runcount) || (thisf_len - readS->pos() <= 1)) {
				return R_FAILURE;
			}

			data_pixel = readS->readByte();

			for (c = 0; c < runcount; c++) {
				*outbuf_p++ = data_pixel;
			}

			outbuf_remain -= runcount;
			continue;
			break;
		case 0x40: // Uncompressed run
			runcount = param_ch + 1;
			if ((outbuf_remain < runcount) || (thisf_len - readS->pos() < runcount)) {
				return R_FAILURE;
			}

			for (c = 0; c < runcount; c++) {
				data_pixel = readS->readByte();
				if (data_pixel != 0) {
					*outbuf_p = data_pixel;
				}
				outbuf_p++;
			}

			outbuf_remain -= runcount;

			continue;
			break;

		default:
			break;
		}
	}

	return R_SUCCESS;
}

int Anim::getFrameOffset(const byte *resdata, size_t resdata_len, uint16 find_frame, size_t *frame_offset_p) {
	R_ANIMATION_HEADER ah;

	uint16 num_frames;
	uint16 current_frame;

	byte mark_byte;
	uint16 control;
	uint16 runcount;
	uint16 magic;

	int i;

	if (!_initialized) {
		return R_FAILURE;
	}

	MemoryReadStream *readS = new MemoryReadStream(resdata, resdata_len);

	// Read animation header
	ah.magic = readS->readUint16LE();
	ah.screen_w = readS->readUint16LE();
	ah.screen_h = readS->readUint16LE();
	ah.unknown06 = readS->readByte();
	ah.unknown07 = readS->readByte();
	ah.nframes = readS->readByte();
	ah.flags = readS->readByte();
	ah.unknown10 = readS->readByte();
	ah.unknown11 = readS->readByte();

	num_frames = ah.nframes;

	if ((find_frame < 1) || (find_frame > num_frames)) {
		return R_FAILURE;
	}

	for (current_frame = 1; current_frame < find_frame; current_frame++) {
		magic = readS->readByte();
		if (magic != SAGA_FRAME_HEADER_MAGIC) {
			// Frame sync failure. Magic Number not found
			return R_FAILURE;
		}

		// skip header
		for (i = 0; i < SAGA_FRAME_HEADER_LEN; i++)
			readS->readByte();

		// For some strange reason, the animation header is in little
		// endian format, but the actual RLE encoded frame data, 
		// including the frame header, is in big endian format. */
		do {
			mark_byte = readS->readByte();
			switch (mark_byte) {
			case 0x3F: // End of frame marker
				continue;
				break;
			case 0x30: // Reposition command
				readS->readByte();
				readS->readByte();
				continue;
				break;
			case 0x2F: // End of row marker
				readS->readByte();
				readS->readByte();
				readS->readByte();
				continue;
				break;
			case 0x20: // Long compressed run marker
				readS->readByte();
				readS->readByte();
				readS->readByte();
				continue;
				break;
			case 0x10: // (16) 0001 0000
				// Long Uncompressed Run
				runcount = readS->readSint16BE();
				for (i = 0; i < runcount; i++)
					readS->readByte();
				continue;
				break;
			default:
				break;
			}

			// Mask all but two high order (control) bits
			control = mark_byte & 0xC0;
			switch (control) {
			case 0xC0:
				// Run of empty pixels
				continue;
				break;
			case 0x80:
				// Run of compressed data
				readS->readByte(); // Skip data byte
				continue;
				break;
			case 0x40:
				// Uncompressed run
				runcount = (mark_byte & 0x3f) + 1;
				for (i = 0; i < runcount; i++)
					readS->readByte();
				continue;
				break;
			default:
				// Encountered unknown RLE marker, abort
				return R_FAILURE;
				break;
			}
		} while (mark_byte != 63);
	}

	*frame_offset_p = readS->pos();
	return R_SUCCESS;
}

void Anim::animInfo(int argc, char *argv[]) {
	uint16 anim_ct;
	uint16 i;
	uint16 idx;

	(void)(argc);
	(void)(argv);

	anim_ct = _anim_count;

	CON_Print("There are %d animations loaded:", anim_ct);

	for (idx = 0, i = 0; i < anim_ct; idx++, i++) {
		while (_anim_tbl[idx] == NULL) {
			idx++;
		}

		CON_Print("%02d: Frames: %u Flags: %u", i, _anim_tbl[idx]->n_frames, _anim_tbl[idx]->flags);
	}
}

static void CF_anim_info(int argc, char *argv[], void *refCon) {
	((Anim *)refCon)->animInfo(argc, argv);
}

} // End of namespace Saga
