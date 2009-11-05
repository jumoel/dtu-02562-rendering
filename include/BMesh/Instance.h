#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include <BMesh/Object.h>
#include "CGLA/Quaternion.h"

namespace BMesh
{
	class Instance {
	public:
		Object *bobject;

		std::string id;
		CGLA::Vec3f translation;
		CGLA::Quaternion rotation;
		Instance();
	};

}
#endif

