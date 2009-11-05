#ifndef __BINSTANCE_H__
#define __BINSTANCE_H__

#include <CGLA/Vec3f.h>
#include <CGLA/Quaternion.h>

namespace BMesh
{
	class BInstance {
	public:

		std::string id;
		CGLA::Vec3f translation;
		CGLA::Quaternion rotation;
	};
}

#endif

