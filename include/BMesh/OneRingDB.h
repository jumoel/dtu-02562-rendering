#ifndef __ONERINGDB_H__
#define __ONERINGDB_H__

#include "TriMesh.h"
#include "OneRing.h"

namespace BMesh
{

	class OneRingDB
	{
		std::vector<OneRing> one_rings;
	
	public:

		OneRingDB(const TriMesh& bmesh);

		const OneRing& get(int i) const
		{
			return one_rings[i];
		}
		
	};

}
#endif
