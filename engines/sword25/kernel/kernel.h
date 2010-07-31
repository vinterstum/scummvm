/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

/* 
 * This code is based on Broken Sword 2.5 engine
 *
 * Copyright (c) Malte Thiesen, Daniel Queteschiner and Michael Elsdoerfer
 *
 * Licensed under GNU GPL v2
 *
 */

/*
 * BS_Kernel
 * ---------
 * This is the main class of the engine.
 * This class creates and manages all other Engine elements: the sound engine, graphics engine ...
 * It is not necessary to release all the items individually, this is performed by the Kernel class.
 *
 * Autor: Malte Thiesen
 */

#ifndef SWORD25_KERNEL_H
#define SWORD25_KERNEL_H

// Includes
#include "common/scummsys.h"
#include "common/random.h"
#include "common/stack.h"
#include "common/util.h"
#include "engines/engine.h"

#include "sword25/kernel/common.h"
#include "sword25/kernel/bs_stdint.h"
#include "sword25/kernel/window.h"
#include "sword25/kernel/resmanager.h"

namespace Sword25 {

// Class definitions
class BS_Service;
class BS_GraphicEngine;
class BS_ScriptEngine;
class BS_SoundEngine;
class BS_InputEngine;
class BS_PackageManager;
class BS_MoviePlayer;

/**
 * This is the main engine class
 *
 * This class creates and manages all other engine components such as sound engine, graphics engine ... 
 * It is not necessary to release all the items individually, this is performed by the Kernel class.
*/
class BS_Kernel {
public:
	// Window methods
	// ----------------

	/**
	 * Returns a pointer to the window object
	 */
	BS_Window *GetWindow() { return _pWindow; }

	// Service Methods
	// ---------------

	/**
	 * Creates a new service with the given identifier. Returns a pointer to the service, or null if the 
	 * service could not be created
 	 * Note: All services must be registered in service_ids.h, otherwise they cannot be created here
	 * @param SuperclassIdentifier		The name of the superclass of the service
	 *		   z.B: "sfx", "gfx", "package" ...
	 * @param ServiceIdentifier			The name of the service
	 *		   For the superclass "sfx" an example could be "Fmod" or "directsound"
	 */
	BS_Service *NewService(const Common::String &SuperclassIdentifier, const Common::String &ServiceIdentifier);

	/**
	 * Ends the current service of a superclass. Returns true on success, and false if the superclass 
	 * does not exist or if not service was active
	 * @param SuperclassIdentfier		The name of the superclass which is to be disconnected
	 *		   z.B: "sfx", "gfx", "package" ...
	 */
	bool DisconnectService(const Common::String &SuperclassIdentifier);

	/**
	 * Returns a pointer to the currently active service object of a superclass
	 * @param SuperclassIdentfier		The name of the superclass
	 *		   z.B: "sfx", "gfx", "package" ...
	 */
	BS_Service *GetService(const Common::String &SuperclassIdentifier);

	/**
	 * Returns the name of the currentl active service object of a superclass.
	 * If an error occurs, then an empty string is returned
	 * @param SuperclassIdentfier		The name of the superclass
	 *		   z.B: "sfx", "gfx", "package" ...
	 */
	Common::String GetActiveServiceIdentifier(const Common::String &SuperclassIdentifier);

	/**
	 * Returns the number of register superclasses
	 */
	unsigned int GetSuperclassCount();

	/**
	 * Returns the name of a superclass with the specified index.
	 * Note: The number of superclasses can be retrieved using GetSuperclassCount
	 * @param Number		The number of the superclass to return the identifier for.
	 * It should be noted that the number should be between 0 und GetSuperclassCount() - 1.
	 */
	Common::String GetSuperclassIdentifier(unsigned int Number);

	/**
	 * Returns the number of services registered with a given superclass
	 * @param SuperclassIdentifier		The name of the superclass
	 *		   z.B: "sfx", "gfx", "package" ...
	 */
	unsigned int GetServiceCount(const Common::String & SuperclassIdentifier);

	/**
	 * Gets the identifier of a service with a given superclass.
	 * The number of services in a superclass can be learned with GetServiceCount().
	 * @param SuperclassIdentifier		The name of the superclass
	 *		   z.B: "sfx", "gfx", "package" ...
	 * @param Number die Nummer des Services, dessen Bezeichner man erfahren will.<br>
	 *		   Hierbei ist zu beachten, dass der erste Service die Nummer 0 erh�lt. Number muss also eine Zahl zwischen
	 *	       0 und GetServiceCount() - 1 sein.
	 */
	Common::String GetServiceIdentifier(const Common::String &SuperclassIdentifier, unsigned int Number);

	/**
	 * Returns the elapsed time since startup in milliseconds
	 */
	unsigned int GetMilliTicks();

	/**
	 * Returns the elapsed time since the system start in microseconds.
	 * This method should be used only if GetMilliTick() for the desired application is inaccurate.
	 */
	uint64 GetMicroTicks();

	/**
	 * Specifies whether the kernel was successfully initialised
	 */
	bool GetInitSuccess() { return _InitSuccess; }
	/**
	 * Returns a pointer to the BS_ResourceManager
	 */
	BS_ResourceManager *GetResourceManager() { return _pResourceManager; }
	/**
	 * Returns how much memory is being used
	 */
	size_t GetUsedMemory();
	/**
	 * Returns a random number
	 * @param Min		The minimum allowed value
	 * @param Max		The maximum allowed value
	 */
	int GetRandomNumber(int Min, int Max);
	/**
	 * Returns a pointer to the active Gfx Service, or NULL if no Gfx service is active
	 */
	BS_GraphicEngine *GetGfx();
	/**
	 * Returns a pointer to the active Sfx Service, or NULL if no Sfx service is active
	 */
	BS_SoundEngine *GetSfx();
	/**
	 * Returns a pointer to the active input service, or NULL if no input service is active
	 */
	BS_InputEngine *GetInput();
	/**
	 * Returns a pointer to the active package manager, or NULL if no manager is active
	 */
	BS_PackageManager *GetPackage();
	/**
	 * Returns a pointer to the script engine, or NULL if it is not active
	 */
	BS_ScriptEngine *GetScript();
	/**
	 * Returns a pointer to the movie player, or NULL if it is not active
	 */
	BS_MoviePlayer *GetFMV();

	/**
	 * Pauses for the specified amount of time
	 * @param Msecs		The amount of time in milliseconds
	 */
	void Sleep(unsigned int Msecs) const;

	/**
	 * Returns the singleton instance for the kernel
	 */
	static BS_Kernel *GetInstance()	{
		if (!_Instance) _Instance = new BS_Kernel();
		return _Instance;
	}

	/**
	 * Destroys the kernel instance
	 * This method should only be called when the game is ended. No subsequent calls to any kernel
	 * methods should be done after calling this method.
	 */
	static void DeleteInstance() {
		if (_Instance) {
			delete _Instance;
			_Instance = NULL;
		}
	}

	/**
	 * Raises an error. This method is used in crashing testing.
	 */
	void Crash() const {
		error("BS_Kernel::Crash");
	}
	
private:
	// -----------------------------------------------------------------------------
	// Constructor / destructor
	// Private singleton methods
	// -----------------------------------------------------------------------------
	
	BS_Kernel();
	virtual ~BS_Kernel();

	// -----------------------------------------------------------------------------
	// Singleton instance
	// -----------------------------------------------------------------------------
	static BS_Kernel *_Instance;

	// Superclass class
	// ----------------
	class Superclass {
	private:
		BS_Kernel *_pKernel;
		unsigned int _ServiceCount;
		Common::String _Identifier;
		BS_Service *_ActiveService;
		Common::String _ActiveServiceName;
		
	public:
		Superclass (BS_Kernel *pKernel, const Common::String &Identifier);
		~Superclass();
		
		unsigned int GetServiceCount() const { return _ServiceCount; }
		Common::String GetIdentifier() const { return _Identifier; }
		BS_Service *GetActiveService() const { return _ActiveService; }
		Common::String GetActiveServiceName() const { return _ActiveServiceName; }
		Common::String GetServiceIdentifier(unsigned int Number);
		BS_Service *NewService(const Common::String &ServiceIdentifier);
		bool DisconnectService();
	};
	
	Common::Array<Superclass*>	_SuperclassList;
	Common::Stack<Common::String>		_ServiceCreationOrder;
	Superclass *GetSuperclassByIdentifier(const Common::String &Identifier);
	
	bool _InitSuccess; // Specifies whether the engine was set up correctly
	bool _Running;	// Specifies whether the application should keep running on the next main loop iteration
	
	// Active window
	// -------------
	BS_Window *_pWindow;

	// Random number generator
	// -----------------------
	Common::RandomSource _rnd;

	/*
	// Features variables and methods
	// ----------------------------------
	enum _CPU_FEATURES_BITMASKS
	{
		_MMX_BITMASK		= (1 << 23),
		_SSE_BITMASK		= (1 << 25),
		_SSE2_BITMASK		= (1 << 26),
		_3DNOW_BITMASK		= (1 << 30),
		_3DNOWEXT_BITMASK	= (1 << 31)
	};

	bool		_DetectCPU();

	bool		_MMXPresent;
	bool		_SSEPresent;
	bool		_SSE2Present;
	bool		_3DNowPresent;
	bool		_3DNowExtPresent;
	CPU_TYPES	_CPUType;
	Common::String	_CPUVendorID;
	*/

	// Resourcemanager
	// ---------------
	BS_ResourceManager *_pResourceManager;

	bool _RegisterScriptBindings();
};

/**
 * This is only a small class that manages the data of a service. It is a little ugly, I know, 
 * but with Common::String a simple struct could not be used.
 */
class BS_ServiceInfo {
public:
	BS_ServiceInfo(const Common::String &SuperclassIdentifier_, const Common::String& ServiceIdentifier_, 
			BS_Service* (*CreateMethod_)(BS_Kernel*)) {
		this->SuperclassIdentifier = SuperclassIdentifier_;
		this->ServiceIdentifier = ServiceIdentifier_;
		this->CreateMethod = CreateMethod_;
	};
	
	Common::String	SuperclassIdentifier;
	Common::String	ServiceIdentifier;
	BS_Service* (*CreateMethod)(BS_Kernel *);
};

}

#endif