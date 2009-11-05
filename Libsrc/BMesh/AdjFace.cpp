#include "BMesh/AdjFace.h"

namespace BMesh
{
 
	AdjFace::AdjFace() {
		for(int i=0;i<3;i++)

			f[i]=static_cast<unsigned int>(-1);
	}
}
