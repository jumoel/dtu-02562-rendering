#ifndef __CAMERA_H
#define __CAMERA_H

#include "CGLA/Vec2f.h"
#include "CGLA/Vec3f.h"
#include "CGLA/Vec3Hf.h"
#include "CGLA/Mat4x4f.h"

/** This class represents an camera and the image plane.
    There are methods for changing viewing parameters, computing the 
    directrion of a viewing ray and performing perspective projection
    (includes viewing transformation and projection). 
    It seems that this class must be useful, because it has survived
    several projects almost unchanged. (I probably should get rid
    of the public variables though */
class Camera
{
  /// Position of camera
  CGLA::Vec3f camera_position;
  /// Point we look at
  CGLA::Vec3f focus_point;  
  /// Direction of up
  CGLA::Vec3f up;  
  /// Direction in which we look
  CGLA::Vec3f line_of_sight;

  /// Basis of camera coordinate system
  CGLA::Vec3f nv,uv,vv;

  /// Distance from camera to image plane in camera coords
  float focal_dist;    

public:

	/** Build the camera from viewing information.
			c is that camera position, f is the point we look at,
			u is the up vector and fd is the distance to the image
			plane. */
	Camera(const CGLA::Vec3f& c, const CGLA::Vec3f& f, 
				 const CGLA::Vec3f& u, const float fd);

  /// Get direction of viewing ray from image coords.
  const CGLA::Vec3f get_ray_direction(const CGLA::Vec2f& p) const;

	/// Returns position of camera.
	const CGLA::Vec3f& get_position() const {return camera_position;}
	
};

#endif
