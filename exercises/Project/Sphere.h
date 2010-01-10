#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Object3D.h"

/** The notion of a sphere should be familiar. A sphere is a solid, hence
		may transmit light. */
class Sphere : public Object3D
{
	CGLA::Vec3f position;
	float radius;
  
public:
	
	CGLA::Vec3f get_normal(const CGLA::Vec3f& surf_point) const;
	
	void transform(const CGLA::Mat4x4f&);
		
	Sphere(const CGLA::Vec3f& pos,
				 Surface * s,
				 const float rad): Object3D(s), position(pos), radius(rad) 
	{
		is_solid = true;
	}
  
	virtual bool intersect(Ray& r) const;
};      
#endif
