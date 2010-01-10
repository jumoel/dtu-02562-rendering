#include <assert.h>
#include "Common/CommonDefs.h"
#include "CGLA/Vec3f.h"
#include "CGLA/Mat4x4f.h"
#include "Camera.h"

using namespace CGLA;
using namespace std;

/// Constructor. The one and only
Camera::Camera(const CGLA::Vec3f& ep, const CGLA::Vec3f& fp, 
							 const CGLA::Vec3f& u, const float fd):
	camera_position(ep), focus_point(fp), up(u), focal_dist(fd)
{
	up.normalize();
	
	// line of sight is calculated on the 
	// basis of the camera position and 
	// focus point
      
	line_of_sight = focus_point - camera_position;
			
	//----------------------------------------------
	// The basis of our coordinate system (nv,uv,vv)
	//----------------------------------------------
      
	nv = line_of_sight;
			
	nv.normalize();  
			
	//   vv = up - nv*dot(nv,up);
	//   vv.normalize();
	//   uv = cross(nv,vv);
			
	uv = cross(nv,up);
	uv.normalize();
			
	vv = cross(uv,nv);
	vv.normalize();
	//recalculate();
};

/// Get direction of viewing ray from image coords.
const CGLA::Vec3f Camera::get_ray_direction(const CGLA::Vec2f& p) const
{
	CGLA::Vec3f dir(nv);
	dir *= focal_dist; 
	dir += uv*p[0];
	dir += vv*p[1];
	//dir.normalize();
	return dir;
};
