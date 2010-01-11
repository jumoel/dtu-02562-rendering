#include <iostream>
#include <cstdlib>  // For random number generator

#include "World.h"
#include "Surface.h"
#include "mathfuncs.h"

using namespace CGLA;
using namespace std;
using namespace CMN;

class tot_int_refl_exception { };

Vec3f Surface::shade(const Ray& incident, const Vec3f& normal, const bool is_solid) const
{
  /* I is the intensity factor which gets multiplied with the
   * color of the object.
   */
  Vec3f I = Vec3f(0.0, 0.0, 0.0);
	
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
  I += k_ambient * world->get_ambient();

  for (int i = 0; i < lights.size(); i++) {
    LightSource *light = lights[i];

    for (int j = 0; j < light->get_no_samples(); j++) {
      L = light->get_position() - incident.get_position();
      L.normalize();

      Ray shadow = Ray(incident.get_position(), L);
      world->first_intersection(shadow);

      if(!shadow.did_hit()) {
        //H = 2*dot(normal, L)*normal - L;
        H = (L + V);
        H.normalize();

        // Lambertian shading (ICG pp. 300-301)
        I += k_diffuse * dot(N, L) * lights[i]->get_intensities() / light->get_no_samples();

        // Phong (specular) highlights (3CG p. 178)
        I += k_highlight * pow(dot(N, H), phong_exponent) * lights[i]->get_intensities() / light->get_no_samples();
        //I += k_highlight * pow(dot(H,V), phong_exponent) * lights[i]->get_intensities() / light->get_no_samples();
      }
    }
  }

  // If the surface is NOT a perfectly diffuse surface, spawn a reflection ray
  /*if (k_diffuse < 1) {
    Ray reflection = reflected_ray(incident, N);

    I += k_reflected * world->trace(reflection);
  }*/

  // Algorithm explanation in 3CG, p. 349
  if (refraction_index > 0) {
    try {
      Ray refracted = refracted_ray(incident, N, refraction_index);

      I += k_transmitted * world->trace(refracted);
    } catch (tot_int_refl_exception) { }
  }
	
  Vec3f irr(0.0, 0.0, 0.0);

  if (!incident.first_intersection) {
    irr = world->get_global_photon_map()->irradiance_estimate(incident.get_position(), N, 0.2, 200);
  } else {
    Ray diffuse = reflected_ray(incident, N);
    world->first_intersection(diffuse);
    if (diffuse.did_hit()) {
      irr = world->get_global_photon_map()->irradiance_estimate(diffuse.get_position(), diffuse.intersected()->get_normal(diffuse.get_position()), 5.0, 200);
    }
  }

  I += k_diffuse * world->get_caustic_photon_map()->irradiance_estimate(incident.get_position(), N, 0.2, 200);

  I += k_diffuse * irr;

  return I * color;
}

/* Calculates a reflected ray off a diffuse surface.
* See 3CG p. 24. */
Ray reflected_ray(const Ray& r, const CGLA::Vec3f& N) {
  // The minus is because the L vector is opposite of the
  // incident direction.
  Vec3f L = -r.get_direction();

  Vec3f R = 2 * dot(N, L) * N - L;

  return Ray(r.get_position(), R, r.get_level() + 1);
}

/* Calculates a refracted ray off a transparent surface.
* See 3CG p. 24. and refr.pdf ("Heckbert's method") */
Ray refracted_ray(const Ray& r, const CGLA::Vec3f& N, float refi) {
  double n = (refi == r.media_refi) ? r.media_refi : r.media_refi / refi;

  Vec3f I = r.get_direction();

  double c1 = -dot(I, N);
  double c2 = 1 - pow(n, 2) * (1 - pow(c1, 2));

  if (c2 < 0) {
    throw tot_int_refl_exception();
  }

  c2 = sqrt(c2);

  Vec3f T = n * I + (n*c1 - c2) * N;

  return Ray(r.get_position(), T, r.get_level() + 1, refi);
}


void Surface::trace_photon(const Ray& r, const Vec3f& normal, const Vec3f& power, const bool is_solid) const
{
  if (r.caustic) {
    trace_caustic_photon(r, normal, power, is_solid);
    return;
  }
  if (k_diffuse > 0) {
    world->get_global_photon_map()->store(power, r.get_position(), r.get_direction());
  }

  Vec3f N;

  // The normal must point outwards
  if (dot(normal, r.get_direction()) > 0) {
    N = - normal;
  } else {
    N = normal;
  }

  float random = rand01();

  // diffuse reflection
  if (random < k_reflected) {
    float ran2 = rand01();

    if (ran2 < k_diffuse) {
      float e0 = rand01();
      float e1 = rand01();
      float cost = sqrt(e0);
      float sint = sqrt(1.f - e0);
      float cosp = cos(e1 * 2.f * float(M_PI));
      float sinp = sin(e1 * 2.f * float(M_PI));
      Vec3f x, y, z = normal;
      Vec3f dir(sint*cosp, sint*sinp, cost);
      orthogonal(z, x, y);
      Vec3f out = dir[0]*x + dir[1]*y + dir[2]*z;

      world->trace_photon(Ray(r.get_position(), out, r.get_level() + 1), power);
    } else {
      Ray reflect = reflected_ray(r, N);
      world->trace_photon(reflect, power);
    }
  }
  // refraction
  else if(random < k_reflected + k_transmitted) {
    try {
      Ray refracted = refracted_ray(r, N, refraction_index);

      world->trace_photon(refracted, power);

      Ray reflected = reflected_ray(r, N);

      world->trace_photon(reflected, power);
    } catch (tot_int_refl_exception) { }
  }
}

void Surface::trace_caustic_photon(const Ray& r, const Vec3f& normal, const Vec3f& power, const bool is_solid) const
{
  if (k_diffuse > 0) {
    world->get_caustic_photon_map()->store(power, r.get_position(), r.get_direction());

    return;
  }

  Vec3f N;

  // The normal must point outwards
  if (dot(normal, r.get_direction()) > 0) {
    N = - normal;
  } else {
    N = normal;
  }

  float random = rand01();

  // diffuse reflection
  if (random < k_reflected) {
    Ray reflect = reflected_ray(r, N);
    world->trace_photon(reflect, power);
  }
  // refraction
  else if(random < k_reflected + k_transmitted) {
    try {
      Ray refracted = refracted_ray(r, N, refraction_index);

      world->trace_photon(refracted, power);

      Ray reflected = reflected_ray(r, N);

      world->trace_photon(reflected, power);
    } catch (tot_int_refl_exception) { }
  }
}