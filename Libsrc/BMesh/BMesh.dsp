# Microsoft Developer Studio Project File - Name="BMesh" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=BMesh - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "BMesh.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "BMesh.mak" CFG="BMesh - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BMesh - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "BMesh - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=xicl6.exe
RSC=rc.exe

!IF  "$(CFG)" == "BMesh - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "BMesh - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BMesh___Win32_Debug"
# PROP BASE Intermediate_Dir "BMesh___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "BMesh___Win32_Debug"
# PROP Intermediate_Dir "BMesh___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=xilink6.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "BMesh - Win32 Release"
# Name "BMesh - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AdjFace.cpp
# End Source File
# Begin Source File

SOURCE=.\AdjFaceList.cpp
# End Source File
# Begin Source File

SOURCE=.\draw.cpp
# End Source File
# Begin Source File

SOURCE=.\Edge.cpp
# End Source File
# Begin Source File

SOURCE=.\Instance.cpp
# End Source File
# Begin Source File

SOURCE=.\load_mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\Material.cpp
# End Source File
# Begin Source File

SOURCE=.\MeshFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\obj_load.cpp
# End Source File
# Begin Source File

SOURCE=.\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\OneRing.cpp
# End Source File
# Begin Source File

SOURCE=.\OneRingDB.cpp
# End Source File
# Begin Source File

SOURCE=.\Parse.cpp
# End Source File
# Begin Source File

SOURCE=.\smooth.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TexCoord.cpp
# End Source File
# Begin Source File

SOURCE=.\Texmap.cpp
# End Source File
# Begin Source File

SOURCE=.\TexmapDraw.cpp
# End Source File
# Begin Source File

SOURCE=.\TriMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\vrml_save.cpp
# End Source File
# Begin Source File

SOURCE=.\x3d_load.cpp
# End Source File
# Begin Source File

SOURCE=.\X3DBMesh.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\BMesh\AdjFace.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\AdjFaceList.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\draw.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\Edge.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\Instance.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\load_mesh.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\loader.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\Material.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\Mesh4FaceModifier.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\MeshFunc.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\obj_load.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\Object.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\OneRing.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\OneRingDB.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\Parse.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\smooth.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\TexCoord.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\Texmap.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\TexmapDraw.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\TriMesh.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\vrml_save.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\x3d_load.h
# End Source File
# Begin Source File

SOURCE=..\include\BMesh\X3DBMesh.h
# End Source File
# End Group
# End Target
# End Project
