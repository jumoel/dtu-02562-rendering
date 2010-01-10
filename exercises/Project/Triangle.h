#ifndef __TINT_TRIANGLE_H
#define __TINT_TRIANGLE_H

#include "CGLA/Vec3f.h"
#include "Object3D.h"

/** The triangle class represents triangles. */
class Triangle : public Object3D
{
	CGLA::Vec3f v0,v1,v2;
	CGLA::Vec3f normal;
public:

	Triangle(const CGLA::Vec3f& _v0, const CGLA::Vec3f& _v1, 
		 const CGLA::Vec3f& _v2, Surface* s):
	  Object3D(s),
	  v0(_v0), v1(_v1), v2(_v2), normal(CGLA::normalize(CGLA::cross(v1-v0,v2-v0)))
	  {
	    is_solid = false;
	  }

	void transform(const CGLA::Mat4x4f& m);
		
	bool intersect(Ray& r) const;

	CGLA::Vec3f get_normal(const CGLA::Vec3f& v) const
	{
		return normal;
	}

};
#endif
