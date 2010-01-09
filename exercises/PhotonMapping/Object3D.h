#ifndef __OBJECT3D_H
#define __OBJECT3D_H

#include "CGLA/Mat4x4f.h"
#include "Surface.h"
#include "Ray.h"

//---------------------------------------------------------------------------
// class Object3D 
//
// This is the abstract ancestor of all traceable objects.
//---------------------------------------------------------------------------

class Object3D 
{
protected:
	// An object contains a surface
	Surface* surf;
	bool is_solid;
	
public:

	Object3D(Surface * s): surf(s) {}

  /** Transform an object. Objects are represented directly in world
			coordinates. This function is used to transform the objects 
			according to an arbitrary transfer matrix. */
	virtual void transform(const CGLA::Mat4x4f& m) = 0;
  
	/// Intersect the object with a ray.
	virtual bool intersect(Ray& r) const = 0;
  

	/** Shade function. This function is called assuming that a ray
			has hit the object. The shade function of the material is 
			immediately called once the intersection point has been 
			established. */
 	virtual CGLA::Vec3f shade(const Ray& ray) const 
	{
		CGLA::Vec3f point = ray.get_position();
		return surf->shade(ray, get_normal(point), is_solid);
	};
  
	/// Return the normal at a given point
	virtual CGLA::Vec3f get_normal(const CGLA::Vec3f& v) const = 0;
};


#endif





