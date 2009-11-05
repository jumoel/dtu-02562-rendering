#ifndef __AABB_H__
#define __AABB_H__

#include <CGLA/Vec3f.h>
#include "Common/CommonDefs.h"

namespace Geometry {
	
	class AABB 
	{
	public:
		CGLA::Vec3f min;
		CGLA::Vec3f max;
		
		AABB();
	};
}
namespace GEO = Geometry;


#endif

