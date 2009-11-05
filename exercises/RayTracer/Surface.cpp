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
   * See p. 298 in "Interactive Computer Graphics" for
   * an explanaition of the vectors.
   */
  Vec3f L, N, V, R;

  /* A list of all the lights in the world.
   */
  const vector<LightSource*>& lights = world->get_light();

  // Ambient light contribution (p. 300)
  I = k_ambient * world->get_ambient();

  N = normal;
  V = -incident.get_direction();

  for (int i = 0; i < lights.size(); i++) {
    L = lights[i]->get_position() - incident.get_position();
    L.normalize();

    // Lambertian shading (pp. 300-301)
    I += k_diffuse * dot(L, N) * lights[i]->get_intensities();
  }
		
  return I * color;
}