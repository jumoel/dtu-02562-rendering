#ifndef __BMESH_X3D_SAVE_H__
#define __BMESH_X3D_SAVE_H__

#include <string>
#include "Object.h"

namespace BMesh
{
	const unsigned char SAVE_VERTEX_NORMALS = 0x01;
	const unsigned char SAVE_VERTEX_COLORS  = 0x02;
	
	bool x3d_save(const std::string& filename, Object&, 
				  unsigned char flags=0);
}


#endif
