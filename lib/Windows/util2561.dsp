# Microsoft Developer Studio Project File - Name="util2561" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=util2561 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "util2561.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "util2561.mak" CFG="util2561 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "util2561 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "util2561 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "util2561 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x406 /d "NDEBUG"
# ADD RSC /l 0x406 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"util2561.lib"

!ELSEIF  "$(CFG)" == "util2561 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"util2561.lib"

!ENDIF 

# Begin Target

# Name "util2561 - Win32 Release"
# Name "util2561 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "CGLA"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Mat2x2f.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Mat3x3f.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Mat4x4f.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Quaternion.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\TableTrigonometry.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Vec2f.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Vec2i.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Vec3f.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\CGLA\Vec3i.cpp
# ADD CPP /I "../../include/CGLA"
# End Source File
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Libsrc\Common\RootSolvers.cpp
# ADD CPP /I "../../include/Common"
# End Source File
# End Group
# Begin Group "Components"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Libsrc\Components\BinSave.cpp
# ADD CPP /I "../../include/Components"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\Components\ResourceLoader.cpp
# ADD CPP /I "../../include/Components"
# End Source File
# End Group
# Begin Group "Graphics"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Libsrc\Graphics\PPMBitmap.cpp
# ADD CPP /I "../../include/Graphics"
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\Graphics\TrackBall.cpp
# ADD CPP /I "../../include/Graphics"
# End Source File
# End Group
# Begin Group "X3DSceneGraph"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\ImageLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\IndexedFaceSet.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\SceneGraph.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\SceneGraphLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\SceneGraphTools.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\TextureLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\TGA.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\X3DSceneGraph\Tools.cpp
# End Source File
# End Group
# Begin Group "Geometry"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\Libsrc\Geometry\AABB.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Libsrc\Geometry\AABBTools.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
