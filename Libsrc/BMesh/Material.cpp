#include "BMesh/Material.h"
#include <string>

namespace BMesh
{

	Material::Material() {
		std::string name;	
		// Default properties
		diffuse_color[0] = 1.0f;
		diffuse_color[1] = 1.0f;
		diffuse_color[2] = 1.0f;
		ambient_intensity = 0.2f;
		specular_color[0] = 0;
		specular_color[1] = 0;
		specular_color[2] = 0;
		emissive_color[0] = 0;
		emissive_color[1] = 0;
		emissive_color[2] = 0;
		shininess = .2f;
		transparency = 0;
	}

}	
