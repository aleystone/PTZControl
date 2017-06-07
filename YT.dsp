# Microsoft Developer Studio Project File - Name="YT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=YT - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "YT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "YT.mak" CFG="YT - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "YT - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "YT - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "YT - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "YT - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "YT - Win32 Release"
# Name "YT - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BitmapBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Com.cpp
# End Source File
# Begin Source File

SOURCE=.\Pelco_D.cpp
# End Source File
# Begin Source File

SOURCE=.\Pelco_P.cpp
# End Source File
# Begin Source File

SOURCE=.\StageLens.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\YT.cpp
# End Source File
# Begin Source File

SOURCE=.\YT.rc
# End Source File
# Begin Source File

SOURCE=.\YTDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BitmapBtn.h
# End Source File
# Begin Source File

SOURCE=.\CheckButton.h
# End Source File
# Begin Source File

SOURCE=.\Com.h
# End Source File
# Begin Source File

SOURCE=.\Pelco_D.h
# End Source File
# Begin Source File

SOURCE=.\Pelco_P.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StageLens.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\YT.h
# End Source File
# Begin Source File

SOURCE=.\YTDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AutoScan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AutoScan_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BottomLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BottomLeft_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BottomRight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BottomRight_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Down.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Down_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Left.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Left_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PTZControl.ico
# End Source File
# Begin Source File

SOURCE=.\res\RainBrush.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RainBrush_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Right.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Right_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SearchLight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SearchLight_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Setting.ico
# End Source File
# Begin Source File

SOURCE=.\res\TopLeft.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TopLeft_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TopRight.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TopRight_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Up.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Up_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\YT.ico
# End Source File
# Begin Source File

SOURCE=.\res\YT.rc2
# End Source File
# Begin Source File

SOURCE=.\res\ZoomIn.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ZoomIn_F.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ZoomOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ZoomOut_F.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
