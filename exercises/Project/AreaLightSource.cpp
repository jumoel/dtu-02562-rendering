#include <cstdlib>  // For random number generator
#include <ctime>    // For time function

#include "LightSource.h"
#include "AreaLightSource.h"
#include "World.h"
#include "mathfuncs.h"

using namespace CGLA;

/*
CGLA::Vec3f get_position();
	CGLA::Vec3f get_normal();
  void emit_photons();
  */

CGLA::Vec3f AreaLightSource::get_position() {
  if (current_sample == 0) {
    t = 0.0;
    s = 0.0;
  } else {
    s += 1.0/((float)num_samples);

    if (current_sample % (num_samples + 1) == 0) {
      s = 0.0;
      t += 1.0/((float)num_samples);
    }
  }

  current_sample = (current_sample + 1) % ((num_samples + 1) * (num_samples + 1));

  return position[0] + s*(position[1] - position[0]) + t*(position[2] - position[0]);
}

void AreaLightSource::emit_photons() {
  int ne = 0;

  float x,y,z;
  float rx,ry;

  Photon_map *pm;

  /* GLOBAL PHOTONS */
  while (ne < world->get_global_photon_map()->get_max_photons()) {
    rx = rand01();
    ry = rand01();

    x = sqrt(1 - ry) * cos(2 * M_PI * rx);
    y = sqrt(1 - ry) * sin(2 * M_PI * rx);
    z = sqrt(ry);

    Vec3f d(x, y, z);
    d.normalize();

    // The vector needs to be in the same hemisphere as the normal
    if (dot(normal, d) < 0)
      d = -d;

    Vec3f p = get_position();

    world->trace_photon(Ray(p, d), get_intensities());

    ne = ne + 1;
  }

  pm = world->get_global_photon_map();

  pm->scale_photon_power(pm->getPhotonCount());
  pm->balance();

  /* CAUSTIC PHOTONS */
  while (ne < world->get_caustic_photon_map()->get_max_photons()) {
    rx = rand01();
    ry = rand01();

    x = sqrt(1 - ry) * cos(2 * M_PI * rx);
    y = sqrt(1 - ry) * sin(2 * M_PI * rx);
    z = sqrt(ry);

    Vec3f d(x, y, z);
    d.normalize();

    // The vector needs to be in the same hemisphere as the normal
    if (dot(normal, d) < 0)
      d = -d;

    Vec3f p = get_position();

    Ray photon = Ray(p, d);
    photon.set_caustic();

    world->trace_photon(photon, get_intensities());

    ne = ne + 1;
  }

  pm = world->get_caustic_photon_map();

  pm->scale_photon_power(pm->getPhotonCount());
  pm->balance();
}