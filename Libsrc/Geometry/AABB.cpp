#include <Geometry/AABB.h>

using namespace CMN;

namespace Geometry {

AABB::AABB() {
	min.set(BIG,BIG,BIG);
	max.set(-BIG,-BIG,-BIG);
}

}
