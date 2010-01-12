#include "Plane.h"
#include <iostream>

using namespace CGLA;
using namespace std;

Plane::Plane(const Vec3f& _pos,
										 const Vec3f& _normal,
										 Surface * s):
	Object3D(s), pos(_pos), normal(normalize(_normal)), 
	d(dot(pos,normal))
{
	is_solid = false;
}

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
  
void Plane::transform(const CGLA::Mat4x4f& m)
{
	pos = m.mul_3D_point(pos);
	normal = m.mul_3D_vector(normal);
};

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------

bool Plane::intersect(Ray& r)
{
	// dir must be normalized ! 
	float dnd;
	if (fabs(dnd = dot(normal,r.get_direction())) > 1e-6)
		{
			r.cond_set_parameter(-(d+dot(r.get_origin(),normal)) / dnd, this);
			return true;
		}
	return false;
}

