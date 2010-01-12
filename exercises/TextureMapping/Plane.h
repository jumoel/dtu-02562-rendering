#ifndef __PLANE_H
#define __PLANE_H

#include "CGLA/Vec3f.h"
#include "CGLA/Vec2f.h"
#include "Object3D.h"

/** Infinite plane object. Not a solid. */
	class Plane : public Object3D
	{
		CGLA::Vec3f pos;
		CGLA::Vec3f normal;
		float d;

  
	public:

		CGLA::Vec3f get_normal(const CGLA::Vec3f& surf_point) const { return normal; }
  
		Plane(const CGLA::Vec3f& _pos,
							const CGLA::Vec3f& _normal,
							Surface * s);
  
		virtual void transform(const CGLA::Mat4x4f& m);

		bool intersect(Ray& r);
	};
#endif
