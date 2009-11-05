#ifndef __AABBTOOLS_H__
#define __AABBTOOLS_H__

#include "AABB.h"
#include <CGLA/Mat4x4f.h>

namespace Geometry {

AABB getBoundingAABB(const AABB& aabb, const CGLA::Mat4x4f& mat);
AABB getBoundingAABB(const AABB& aabb1, const AABB& aabb2);

}

#endif
