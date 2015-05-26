# Microsoft Developer Studio Project File - Name="EVENTLOG" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=EVENTLOG - Win32 Unicode Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "EVENTLOG.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "EVENTLOG.MAK" CFG="EVENTLOG - Win32 Unicode Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "EVENTLOG - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "EVENTLOG - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "EVENTLOG - Win32 Unicode Release" (based on "Win32 (x86) Static Library")
!MESSAGE "EVENTLOG - Win32 Unicode Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "EVENTLOG - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Release"
# PROP Intermediate_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zd /O2 /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /I "\VR\VR_CLASS\CLIENTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MULTILANG" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "\VR\VR_DLG" /i "\VR\VR_CLASS\CLIENTS" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"o:\vr\VR_LIB\EVENTLOG.lib"

!ELSEIF  "$(CFG)" == "EVENTLOG - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Debug"
# PROP Intermediate_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /I "\VR\VR_CLASS\CLIENTS" /I "J:\VR\VR_CLASS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MULTILANG" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "\VR\VR_DLG" /i "\VR\VR_CLASS\CLIENTS" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"o:\vr\VR_LIB\EVENTLOGd.lib"

!ELSEIF  "$(CFG)" == "EVENTLOG - Win32 Unicode Release"

# PROP BASE Use_MFC 1
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "EVENTLOG___Win32_Unicode_Release"
# PROP BASE Intermediate_Dir "EVENTLOG___Win32_Unicode_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 1
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Unicode_Release"
# PROP Intermediate_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Unicode_Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /Zd /O2 /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /I "\VR\VR_CLASS\CLIENTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "MULTILANG" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zd /O2 /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /I "\VR\VR_CLASS\CLIENTS" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "UNICODE" /D "_UNICODE" /D "MULTILANG" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /i "\VR\VR_DLG" /i "\VR\VR_CLASS\CLIENTS" /d "NDEBUG"
# ADD RSC /l 0x419 /i "\VR\VR_DLG" /i "\VR\VR_CLASS\CLIENTS" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\VR_LIB\EVENTLOG.lib"
# ADD LIB32 /nologo /out:"o:\vr\VR_LIB\EVENTLOGU.lib"

!ELSEIF  "$(CFG)" == "EVENTLOG - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "EVENTLOG___Win32_Unicode_Debug"
# PROP BASE Intermediate_Dir "EVENTLOG___Win32_Unicode_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Unicode_Debug"
# PROP Intermediate_Dir "O:\VR\TMP\VR_CLASS\EVENTLOG\Unicode_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /I "\VR\VR_CLASS\CLIENTS" /I "J:\VR\VR_CLASS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "MULTILANG" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "\VR\VR_INC" /I "\VR\VR_DLG" /I "\VR\VR_CLASS" /I "\VR\VR_CLASS\CLIENTS" /I "J:\VR\VR_CLASS" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "UNICODE" /D "_UNICODE" /D "MULTILANG" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE RSC /l 0x419 /i "\VR\VR_DLG" /i "\VR\VR_CLASS\CLIENTS" /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /i "\VR\VR_DLG" /i "\VR\VR_CLASS\CLIENTS" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"..\..\VR_LIB\EVENTLOGd.lib"
# ADD LIB32 /nologo /out:"o:\vr\VR_LIB\EVENTLOGUd.lib"

!ENDIF 

# Begin Target

# Name "EVENTLOG - Win32 Release"
# Name "EVENTLOG - Win32 Debug"
# Name "EVENTLOG - Win32 Unicode Release"
# Name "EVENTLOG - Win32 Unicode Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Event.cpp
# End Source File
# Begin Source File

SOURCE=.\EventBase.cpp
# End Source File
# Begin Source File

SOURCE=.\EventClass.cpp
# End Source File
# Begin Source File

SOURCE=.\EventDBG.cpp
# End Source File
# Begin Source File

SOURCE=.\EventEx.cpp
# End Source File
# Begin Source File

SOURCE=.\EventLog.cpp
# End Source File
# Begin Source File

SOURCE=.\EventObj.cpp
# End Source File
# Begin Source File

SOURCE=.\EventRsz.cpp
# End Source File
# Begin Source File

SOURCE=.\EventWin.cpp
# End Source File
# Begin Source File

SOURCE=.\EvntApp.cpp
# End Source File
# Begin Source File

SOURCE=.\EvntChan.cpp
# End Source File
# Begin Source File

SOURCE=.\EvntData.cpp
# End Source File
# Begin Source File

SOURCE=.\EvntMIDI.cpp
# End Source File
# Begin Source File

SOURCE=.\EvntPort.cpp
# End Source File
# Begin Source File

SOURCE=.\EvntStr.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Event.h
# End Source File
# Begin Source File

SOURCE=.\Event.inl
# End Source File
# Begin Source File

SOURCE=.\EventBase.h
# End Source File
# Begin Source File

SOURCE=.\EventBase.inl
# End Source File
# Begin Source File

SOURCE=.\EventClass.h
# End Source File
# Begin Source File

SOURCE=.\EventClass.inl
# End Source File
# Begin Source File

SOURCE=.\EventEx.h
# End Source File
# Begin Source File

SOURCE=.\EventEx.inl
# End Source File
# Begin Source File

SOURCE=.\EventLog.h
# End Source File
# Begin Source File

SOURCE=.\EventLog.inl
# End Source File
# Begin Source File

SOURCE=.\EventObj.h
# End Source File
# Begin Source File

SOURCE=.\EventObj.inl
# End Source File
# Begin Source File

SOURCE=.\Events.h
# End Source File
# Begin Source File

SOURCE=.\EventWin.h
# End Source File
# Begin Source File

SOURCE=.\EvntApp.h
# End Source File
# Begin Source File

SOURCE=.\EvntApp.inl
# End Source File
# Begin Source File

SOURCE=.\EvntChan.h
# End Source File
# Begin Source File

SOURCE=.\EvntChan.inl
# End Source File
# Begin Source File

SOURCE=.\EvntData.h
# End Source File
# Begin Source File

SOURCE=.\EvntData.inl
# End Source File
# Begin Source File

SOURCE=.\EvntInfo.h
# End Source File
# Begin Source File

SOURCE=.\EvntMIDI.H
# End Source File
# Begin Source File

SOURCE=.\EvntMIDI.inl
# End Source File
# Begin Source File

SOURCE=.\EvntPort.H
# End Source File
# Begin Source File

SOURCE=.\EvntPort.INL
# End Source File
# Begin Source File

SOURCE=.\EvntStr.h
# End Source File
# Begin Source File

SOURCE=.\EvntStr.inl
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\MM\MMEvent.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Xpackage"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\VR_INC\INT64.H
# End Source File
# Begin Source File

SOURCE=..\..\VR_TOOLS\SRSLogView\xCExcept.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_TOOLS\SRSLogView\xCString.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\xCSyncOb.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\xGUID.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\XLOG.H
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\xnew.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\xstring.h
# End Source File
# End Group
# Begin Group "Ypackage"

# PROP Default_Filter ""
# Begin Group "_common_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\VR_INC\YClass.h
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\YClass.inl
# End Source File
# Begin Source File

SOURCE=..\..\VR_INC\YTime.h
# End Source File
# End Group
# Begin Group "MM"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\VR_INC\MM\MM4cc.h
# End Source File
# End Group
# Begin Group "OS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\VR_INC\OS\OsLock.h
# End Source File
# End Group
# End Group
# End Target
# End Project
