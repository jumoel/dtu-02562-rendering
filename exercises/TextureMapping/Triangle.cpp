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

bool Triangle::intersect(Ray& r)
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
	
	bool ret = r.cond_set_parameter(t, this);

  if (ret) {
    Vec3f v0v1 = Vec3f(v1[0] - v0[0], v1[1] - v0[1], v1[2] - v0[2]);
    Vec3f v0v2 = Vec3f(v2[0] - v0[0], v2[1] - v0[1], v2[2] - v0[2]);

    float v0v1_l = v0v1.length();
    float v0v2_l = v0v2.length();
    float angle = acos(dot(v0v1, v0v2) / (v0v1_l * v0v2_l));

    Vec2f a,b,c;
    a = Vec2f(0.0, 0.0);
    b = Vec2f(v0v1_l, 0.0);
    c = Vec2f(v0v2_l * cos(angle), v0v2_l * sin(angle));

    float x_min, x_max, y_min, y_max;
    x_min = min(min(a[0], b[0]), c[0]);
    x_max = max(max(a[0], b[0]), c[0]);
    y_min = min(min(a[1], b[1]), c[1]);
    y_max = max(max(a[1], b[1]), c[1]);

    float x_dist, y_dist;
    x_dist = x_max - x_min;
    y_dist = y_max - y_min;

    float max_dist;

    if (x_dist < y_dist)
      max_dist = y_dist;
    else
      max_dist = x_dist;
     

    Vec2f st0 = Vec2f(0.0, 0.0);
    Vec2f st1 = Vec2f(b[0] / max_dist, 0.0);
    Vec2f st2 = Vec2f(c[0] / max_dist, c[1] / max_dist);

    Vec2f texcoord = (1.0 - u - v) * st0 + u * st1 + v * st2;

    r.texturecoords = texcoord;
  }

  return ret;
}
