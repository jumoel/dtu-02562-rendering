#include <iostream>

#include "World.h"
#include "Surface.h"

using namespace CGLA;
using namespace std;
using namespace CMN;

Vec3f Surface::shade(const Ray& incident,
		     const Vec3f& normal,
		     const bool is_solid) const
{
  /* I is the intensity factor which gets multiplied with the
   * color of the object.
   */
  Vec3f I = Vec3f();
	
  /* The vectors used by the Phong lighting model.
   * See p. 298 and pp. 303-304 in "Interactive Computer
   * Graphics" (ICG) and for an explanaition of the vectors.
   * Also see chapter 6.2.1 in "3D Computer Graphics" (3CG).
   */
  Vec3f L, N, V, H;

  /* A list of all the lights in the world.
   */
  const vector<LightSource*>& lights = world->get_light();

  /* The normal vector must always be pointing outwards.
   */
  if (dot(normal, incident.get_direction()) > 0) {
    N = - normal;
  } else {
    N = normal;
  }

  V = -incident.get_direction();

  // Ambient light contribution (ICG p. 300)
  I = k_ambient * world->get_ambient();

  for (int i = 0; i < lights.size(); i++) {
    L = lights[i]->get_position() - incident.get_position();
    L.normalize();

    H = (L + V);
    H.normalize();

    // Lambertian shading (ICG pp. 300-301)
    I += k_diffuse * dot(N, L) * lights[i]->get_intensities();

    // Phong (specular) highlights (3CG p. 178)
    I += k_highlight * pow(dot(N, H), phong_exponent) * lights[i]->get_intensities();
  }
		
  return I * color;
}