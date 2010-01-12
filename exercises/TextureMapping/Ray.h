#ifndef __TINT_RAY_H
#define __TINT_RAY_H

#include <float.h>

#include "CGLA/Vec3f.h"
#include "CGLA/Vec2f.h"

class Object3D;

/** This is a constant used to dismiss intersections very close to previous
intersections. */
const float SMALLEST_DIST = 1e-4;

/// This is the refraction index of air. 
const float DEFAULT_REFRACTION_INDEX = 1.0;

/** The Ray class is used to find intersections between a ray and the scene,
but it also stores information. For instance the Ray remembers intersection
points, and the refraction index of material it is passing through. */
class Ray
{

  /* Makes the reflected_ray and refracted_ray methods have as
  * many rights as a method in a Ray object.
  */
  friend Ray reflected_ray(const Ray& r, const CGLA::Vec3f& N);
  friend Ray refracted_ray(const Ray& r, const CGLA::Vec3f& N, float refi);

  /// Origin of the ray
  const CGLA::Vec3f origin;

  /// The normalized direction of the ray
  CGLA::Vec3f direction;

  /// The parameter -i.e. the distance we have traversed along the ray
  float t;

  /// has the ray hit something ?!
  bool hit;                      

  /// the object that has been hit
  const Object3D* obj;           

  /// Level is the number of times the ray has been traced recursively.
  int level;

  /** Media refraction index of the material currently being traversed.
  When entering a material the refi of the material is stored in the 
  ray. Thus we can compute the required ratio of indices the next time
  an interface is crossed. */
  float media_refi;

public:

  CGLA::Vec2f texturecoords;

  /** Construct a ray. First argument is position. Second argument
  is the direction of the ray. The magnitude of the second argument
  is construed as the step length. */  
  Ray(const CGLA::Vec3f& p, const CGLA::Vec3f& d, 
    int _level=0, float _media_refi = DEFAULT_REFRACTION_INDEX):
  origin(p),
    direction(d),
    t(FLT_MAX),	
    hit(false),
    level(_level),
    media_refi(_media_refi)
  {
    direction.normalize();
  }

    /// Get ray position.
    const CGLA::Vec3f get_position() const {return origin+t*direction;}

  /// Get ray origin.
  const CGLA::Vec3f& get_origin() const {return origin;}

  /// Get ray parameter.
  float get_parameter() const {return t;}

  /// Get direction of ray.
  const CGLA::Vec3f& get_direction() const {return direction;}

  /** Conditional set parameter. Set parameter only if it corresponds
  to a closer hit point than stored parameter. Set the associated
  object. */
  bool cond_set_parameter(const float par, const Object3D * o);

  /// Returns true if ray has hit an object.
  bool did_hit() const {return hit;}

  /// If ray has hit, return intersected object.
  const Object3D* intersected() const {return obj;}

  int get_level() const {return level;}
};

#endif