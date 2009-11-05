#include <Geometry/AABBTools.h>
#include <CGLA/Vec3Hf.h>

using namespace CGLA;
using namespace CMN;

namespace Geometry {

// Purpose is to find an AABB the contains another 
// axis aligned bouding box that has been transformed

AABB getBoundingAABB(const AABB& aabb, const Mat4x4f& mat) 
{
	// Is the bv a legal bv ??
	if (aabb.min[0]>aabb.max[0] || aabb.min[1]>aabb.max[1] ||
			aabb.min[2]>aabb.max[2])
		return aabb;
	// A non optimized method is to find all 8 point and transform 
	// these points using the bounding box and find the min and max of these points
	int i;
	AABB result;

	for (i=0;i<8;i++) {
		// Create all the 8 points in the AABB 
		Vec3Hf point(aabb.min);
		if ((i&1)!=0) point[0] = aabb.max[0];
		if ((i&2)!=0) point[1] = aabb.max[1];
		if ((i&4)!=0) point[2] = aabb.max[2];
		// Transform by the matrix
		Vec3Hf new_point = (mat) * point;
		// Is this point a maximum?
		for(int j=0;j<3;j++) {
			if (new_point[j]<result.min[j])
				result.min[j]=new_point[j];
			if (new_point[j]>result.max[j])
				result.max[j]=new_point[j];
		}		
	}
	return result;
}

AABB getBoundingAABB(const AABB& aabb1, const AABB& aabb2) {
	AABB result;
	for(int i=0;i<3;i++) {
		if (aabb1.min[i]<aabb2.min[i])
			result.min[i]=aabb1.min[i];
		else
			result.min[i]=aabb2.min[i];

		if (aabb1.max[i]>aabb2.max[i])
			result.max[i]=aabb1.max[i];
		else
			result.max[i]=aabb2.max[i];

	}
	return result;
}

}
