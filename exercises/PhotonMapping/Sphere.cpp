#include "CGLA/Vec3f.h"
#include "Sphere.h"

using namespace std;
	using namespace CGLA;

	Vec3f Sphere::get_normal(const Vec3f& surf_point) const 
	{
		Vec3f norm = surf_point - position;
		norm.normalize();
		return norm;
	}

	void Sphere::transform(const Mat4x4f& m)
	 {
	   Vec3f radius_vec = m.mul_3D_point(Vec3f(radius,0,0)+position);
	   position = m.mul_3D_point(position); 
	   // The radius is scaled by the X scaling factor.
	   // Not ideal, but the best we can do without elipsoids
	   radius_vec -= position;
	   radius = radius_vec.length();
	 }

	bool Sphere::intersect(Ray& r) const
	{
		Vec3f sphere2ray_pos = r.get_origin() - position;
  
		float A = 1;
		float B = 2 * dot(sphere2ray_pos, r.get_direction());
		float C = dot(sphere2ray_pos, sphere2ray_pos)
			- radius * radius;

		float Disc = B*B-4*A*C;
		if (Disc >= 0)
			{
				float t;

				if (Disc == 0)
					{
						t = - B / 2 * A;
						r.cond_set_parameter(t, this);
						return true;
					}
				else
					{
						// Calculate both intersections
						float Disc_sqrt = sqrt(Disc);
						float t1 = (- B + Disc_sqrt) / 2 * A;
						float t2 = (- B - Disc_sqrt) / 2 * A;

						bool b1 = r.cond_set_parameter(t1, this);
						bool b2 = r.cond_set_parameter(t2, this);
						return b1||b2;
					}
			}
		else
			return false;
	}

