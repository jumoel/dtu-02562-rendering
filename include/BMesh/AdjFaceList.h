#ifndef __ADJFACELIST_H__
#define __ADJFACELIST_H__

#include <vector>

#include "AdjFace.h"
#include "TriMesh.h"

namespace BMesh
{

	class AdjFaceList {
	public:
		std::vector<AdjFace> adjfaces;
		AdjFaceList(TriMesh& mesh);
	};

}
#endif
