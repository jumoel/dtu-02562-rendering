#ifndef __MATERIAL_H__
#define	__MATERIAL_H__

#include <string>
#include <CGLA/Vec3f.h>

namespace BMesh
{
	class Material {
	public:
		Material();

		std::string name;
		CGLA::Vec3f diffuse_color;
		CGLA::Vec3f specular_color;
		CGLA::Vec3f emissive_color;

		float shininess;
		float transparency;
		float ambient_intensity;
		float alpha;


	};

}
#endif
