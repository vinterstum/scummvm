# Microsoft Developer Studio Project File - Name="scummvm" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=scummvm - Win32 MP3 Enabled Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "scummvm.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "scummvm.mak" CFG="scummvm - Win32 MP3 Enabled Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "scummvm - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "scummvm - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "scummvm - Win32 MP3 Enabled Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "scummvm - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MD /W3 /O2 /Ob2 /I "." /I "sound" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "USE_ADLIB" /D "COMPRESSED_SOUND_FILE" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x41d /d "NDEBUG"
# ADD RSC /l 0x41d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib sdl.lib winmm.lib wsock32.lib libmad.lib /nologo /subsystem:console /machine:I386
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "./sound" /I "./" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ALLOW_GDI" /D "BYPASS_COPY_PROT" /D "DUMP_SCRIPTS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib sdl.lib winmm.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "scummvm___Win32_MP3_Enabled_Debug"
# PROP BASE Intermediate_Dir "scummvm___Win32_MP3_Enabled_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "scummvm___Win32_MP3_Enabled_Debug"
# PROP Intermediate_Dir "scummvm___Win32_MP3_Enabled_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /I "./sound" /I "./" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ALLOW_GDI" /D "BYPASS_COPY_PROT" /D "USE_ADLIB" /D "DUMP_SCRIPTS" /D "COMPRESSED_SOUND_FILE" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT BASE CPP /Fr
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "./sound" /I "./" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "ALLOW_GDI" /D "BYPASS_COPY_PROT" /D "USE_ADLIB" /D "DUMP_SCRIPTS" /D "COMPRESSED_SOUND_FILE" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE RSC /l 0x41d /d "_DEBUG"
# ADD RSC /l 0x41d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib sdl.lib winmm.lib libmad.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib sdl.lib winmm.lib libmad.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "scummvm - Win32 Release"
# Name "scummvm - Win32 Debug"
# Name "scummvm - Win32 MP3 Enabled Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sound\fmopl.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\imuse.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\imuse.h
# End Source File
# Begin Source File

SOURCE=.\sound\mididrv.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\mididrv.h
# End Source File
# Begin Source File

SOURCE=.\sound\mixer.cpp
# End Source File
# Begin Source File

SOURCE=.\sound\mixer.h
# End Source File
# End Group
# Begin Group "v3"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\v3\resource_v3.cpp
# End Source File
# End Group
# Begin Group "v4"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\v4\resource_v4.cpp
# End Source File
# End Group
# Begin Group "simon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\simon\midi.cpp
# End Source File
# Begin Source File

SOURCE=.\simon\simon.cpp
# End Source File
# Begin Source File

SOURCE=.\simon\simon.h
# End Source File
# Begin Source File

SOURCE=.\simon\simondebug.cpp
# End Source File
# Begin Source File

SOURCE=.\simon\simonitems.cpp
# End Source File
# Begin Source File

SOURCE=.\simon\simonres.cpp
# End Source File
# Begin Source File

SOURCE=.\simon\simonsys.cpp
# End Source File
# Begin Source File

SOURCE=.\simon\simonverb.cpp
# End Source File
# Begin Source File

SOURCE=.\simon\simonvga.cpp
# End Source File
# End Group
# Begin Group "gui"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\gui\dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\gui\dialog.h
# End Source File
# Begin Source File

SOURCE=.\gui\ListWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\gui\ListWidget.h
# End Source File
# Begin Source File

SOURCE=.\newgui.cpp
# End Source File
# Begin Source File

SOURCE=.\newgui.h
# End Source File
# Begin Source File

SOURCE=.\gui\ScrollBarWidget.cpp
# End Source File
# Begin Source File

SOURCE=.\gui\ScrollBarWidget.h
# End Source File
# Begin Source File

SOURCE=.\util.cpp
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# Begin Source File

SOURCE=.\gui\widget.cpp
# End Source File
# Begin Source File

SOURCE=.\gui\widget.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\actor.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\akos.cpp
# End Source File
# Begin Source File

SOURCE=.\boxes.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\bundle.cpp
# End Source File
# Begin Source File

SOURCE=".\config-file.cpp"
# End Source File
# Begin Source File

SOURCE=.\costume.cpp
# End Source File
# Begin Source File

SOURCE=.\debug.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gameDetector.cpp
# End Source File
# Begin Source File

SOURCE=.\gfx.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\gui.cpp
# End Source File
# Begin Source File

SOURCE=.\init.cpp
# End Source File
# Begin Source File

SOURCE=.\insane.cpp
# End Source File
# Begin Source File

SOURCE=.\main.cpp
# End Source File
# Begin Source File

SOURCE=.\object.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\saveload.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\scaler.cpp
# End Source File
# Begin Source File

SOURCE=.\script.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\script_v1.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\script_v2.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\scummvm.cpp
# End Source File
# Begin Source File

SOURCE=.\scummvm.rc
# End Source File
# Begin Source File

SOURCE=.\sdl.cpp
# End Source File
# Begin Source File

SOURCE=.\sound.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\string.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sys.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\timer.cpp
# End Source File
# Begin Source File

SOURCE=.\vars.cpp
# End Source File
# Begin Source File

SOURCE=.\verbs.cpp

!IF  "$(CFG)" == "scummvm - Win32 Release"

# ADD CPP /Gd

!ELSEIF  "$(CFG)" == "scummvm - Win32 Debug"

!ELSEIF  "$(CFG)" == "scummvm - Win32 MP3 Enabled Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\actor.h
# End Source File
# Begin Source File

SOURCE=.\akos.h
# End Source File
# Begin Source File

SOURCE=.\boxes.h
# End Source File
# Begin Source File

SOURCE=.\bundle.h
# End Source File
# Begin Source File

SOURCE=.\cdmusic.h
# End Source File
# Begin Source File

SOURCE=".\config-file.h"
# End Source File
# Begin Source File

SOURCE=.\sound\fmopl.h
# End Source File
# Begin Source File

SOURCE=.\gameDetector.h
# End Source File
# Begin Source File

SOURCE=.\gfx.h
# End Source File
# Begin Source File

SOURCE=.\gui.h
# End Source File
# Begin Source File

SOURCE=.\guimaps.h
# End Source File
# Begin Source File

SOURCE=.\scumm.h
# End Source File
# Begin Source File

SOURCE=.\scummsys.h
# End Source File
# Begin Source File

SOURCE=.\smush.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\system.h
# End Source File
# Begin Source File

SOURCE=.\timer.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\scummvm.ico
# End Source File
# End Target
# End Project
