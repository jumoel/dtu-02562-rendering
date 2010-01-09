#include "Triangle.h"

using namespace CGLA;
using namespace std;

	//---------------------------------------------------------------------------
	//
	//---------------------------------------------------------------------------

	void Triangle::transform(const Mat4x4f& m)
	{
		v0 = m.mul_3D_point(v0);
		v1 = m.mul_3D_point(v1);
		v2 = m.mul_3D_point(v2);
		normal = normalize(cross(v1 - v0, v2 - v0 ));
	};


	//---------------------------------------------------------------------------
	//
	//---------------------------------------------------------------------------

bool Triangle::intersect(Ray& r) const
{
	const float EPSILON = 1e-6f;


	Vec3f edge1, edge2, tvec, pvec, qvec;
	float det,inv_det;
	float t,u,v;
	 
	/* find vectors for two edges sharing v0 */
	edge1= v1- v0;
	edge2= v2- v0;
	 

	/* begin calculating determinant - also used to calculate U parameter */
	pvec = cross( r.get_direction(), edge2);

	/* if determinant is near zero, ray lies in plane of triangle */
	det = dot(edge1, pvec);

	if (det > -EPSILON && det < EPSILON)
		return false;
	inv_det = 1.0 / det;


	/* calculate distance from v0 to ray origin */
	tvec= r.get_origin() - v0;

	/* calculate U parameter and test bounds */
	u = dot(tvec, pvec) * inv_det;
	if (u < 0.0 || u > 1.0)
		return false;

	/* prepare to test V parameter */
	qvec = cross( tvec, edge1);

	/* calculate V parameter and test bounds */
	v = dot(r.get_direction(), qvec) * inv_det;
	if (v < 0.0 || u + v > 1.0)
		return false;

	/* calculate t, ray intersects triangle */
	t = dot(edge2, qvec) * inv_det;
	
	return r.cond_set_parameter(t, this);
}
