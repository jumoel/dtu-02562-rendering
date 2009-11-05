#include <BMesh/Instance.h>

using namespace CGLA;

namespace BMesh
{
	Instance::Instance() {
		rotation.make_rot(0,Vec3f(1,0,0));
	}
}
