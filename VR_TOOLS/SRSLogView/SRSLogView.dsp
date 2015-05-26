# Microsoft Developer Studio Project File - Name="SRSLogView" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SRSLogView - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SRSLogView.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SRSLogView.mak" CFG="SRSLogView - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SRSLogView - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SRSLogView - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "SRSLogView - Win32 Unicode Release" (based on "Win32 (x86) Application")
!MESSAGE "SRSLogView - Win32 Unicode Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/SRSLogView", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SRSLogView - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Release"
# PROP Intermediate_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zd /O2 /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "D~EBUG_EL" /D "D~EBUG_EL_TIME" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "\VR\VR_CLASS" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /debugtype:both /machine:I386 /out:"J:\VR\BIN\Release\VR_TOOLS\SRSLogView\SRSLogView.exe"
# Begin Special Build Tool
TargetPath=\VR\BIN\Release\VR_TOOLS\SRSLogView\SRSLogView.exe
TargetName=SRSLogView
SOURCE="$(InputPath)"
PostBuild_Cmds=call _VERSION.BAT /RELEASE $(TargetName) "$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SRSLogView - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Debug"
# PROP Intermediate_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "D~EBUG_EL" /D "K~_DEBUG" /D "D~EBUG_EL_TIME" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "\VR\VR_CLASS" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /profile /map /debug /debugtype:both /machine:I386 /out:"J:\VR\BIN\Debug\VR_TOOLS\SRSLogView\Debug\SRSLogView.exe"
# Begin Special Build Tool
TargetPath=\VR\BIN\Debug\VR_TOOLS\SRSLogView\Debug\SRSLogView.exe
TargetName=SRSLogView
SOURCE="$(InputPath)"
PostBuild_Cmds=call _VERSION.BAT /DEBUG $(TargetName) "$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SRSLogView - Win32 Unicode Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SRSLogView___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "SRSLogView___Win32_Unicode_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Unicode_Release"
# PROP Intermediate_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Unicode_Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MT /W3 /GX /Zd /O2 /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "D~EBUG_EL" /D "D~EBUG_EL_TIME" /Fr /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zd /O2 /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /D "D~EBUG_EL" /D "D~EBUG_EL_TIME" /Fr /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /i "\VR\VR_CLASS" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /debugtype:both /machine:I386 /out:"J:\VR\BIN\Release\VR_TOOLS\SRSLogView\SRSLogView.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /debugtype:both /machine:I386 /out:"J:\VR\BIN\ReleaseU\VR_TOOLS\SRSLogView\SRSLogView.exe"
# Begin Special Build Tool
TargetPath=\VR\BIN\ReleaseU\VR_TOOLS\SRSLogView\SRSLogView.exe
TargetName=SRSLogView
SOURCE="$(InputPath)"
PostBuild_Cmds=call _VERSION.BAT /RELEASEU $(TargetName) "$(TargetPath)"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "SRSLogView - Win32 Unicode Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SRSLogView___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "SRSLogView___Win32_Unicode_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Unicode_Debug"
# PROP Intermediate_Dir "O:\VR\TMP\VR_TOOLS\SRSLogView\Unicode_Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
F90=fl32.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "D~EBUG_EL" /D "K~_DEBUG" /D "D~EBUG_EL_TIME" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /D "~DEBUG_EL" /D "K~_DEBUG" /D "D~EBUG_EL_TIME" /D "DEBUG_DETAIL_STATUS" /D "MULTILANGSTRINGS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "\VR\VR_CLASS" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /profile /debug /machine:I386 /out:"J:\VR\BIN\Debug\VR_TOOLS\SRSLogView\Debug\SRSLogView.exe"
# ADD LINK32 /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /profile /debug /machine:I386 /out:"J:\VR\BIN\DebugU\VR_TOOLS\SRSLogView\SRSLogView.exe"
# Begin Special Build Tool
TargetPath=\VR\BIN\DebugU\VR_TOOLS\SRSLogView\SRSLogView.exe
TargetName=SRSLogView
SOURCE="$(InputPath)"
PostBuild_Cmds=call _VERSION.BAT /DEBUGU $(TargetName) "$(TargetPath)"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "SRSLogView - Win32 Release"
# Name "SRSLogView - Win32 Debug"
# Name "SRSLogView - Win32 Unicode Release"
# Name "SRSLogView - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\_VERSION.CPP
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\EventsFilterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SRSLogView.cpp
# End Source File
# Begin Source File

SOURCE=.\SRSLogView.rc
# End Source File
# Begin Source File

SOURCE=.\SRSLogViewDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\SRSLogViewView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\_VERSION.H
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\EventsFilterDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SRSLogView.h
# End Source File
# Begin Source File

SOURCE=.\SRSLogViewDoc.h
# End Source File
# Begin Source File

SOURCE=.\SRSLogViewView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\new.ico
# End Source File
# Begin Source File

SOURCE=.\res\Phone.ico
# End Source File
# Begin Source File

SOURCE=..\..\VR_RES\SRS.BMP
# End Source File
# Begin Source File

SOURCE=.\SRS.BMP
# End Source File
# Begin Source File

SOURCE=.\res\SRSLogView.ico
# End Source File
# Begin Source File

SOURCE=.\res\SRSLogView.rc2
# End Source File
# Begin Source File

SOURCE=.\res\SRSLogViewDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Windows"

# PROP Default_Filter ""
# Begin Group "EventLogLib"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsFilter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsFilter.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsListDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsListDlg.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsListDlg.inl
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsPage.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\EventsPage.inl
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\HeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\CONTROLS\HeaderCtrl.h
# End Source File
# End Group
# End Group
# Begin Group "Packages"

# PROP Default_Filter ""
# Begin Group "X"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\VR_INC\xCDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\xCExcept.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\xCString.cpp
# End Source File
# End Group
# End Group
# Begin Group "EVENTLOG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\EventDMP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\EventRsz.cpp
# End Source File
# Begin Source File

SOURCE=..\..\VR_CLASS\EVENTLOG\EventZIP.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
