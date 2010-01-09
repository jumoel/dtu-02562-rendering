#include <cstdlib>  // For random number generator
#include <ctime>    // For time function

#include "LightSource.h"
#include "World.h"

using namespace CGLA;

// Returns random number in range [-1;1]
float random()
{
  return 2*rand()/static_cast<float>(RAND_MAX) - 1;
}

void PointLightSource::emit_photons() {
    int ne = 0;

    float x, y, z;
    float length;

    while (ne < world->get_photon_map()->get_max_photons()) {
      do {
        x = random();
        y = random();
        z = random();
        length = x*x + y*y + z*z;
      } while ( length > 1 );

      Vec3f d = Vec3f(x, y, z);
      Vec3f p = get_position();

      world->trace_photon(Ray(p, d), get_intensities() / world->get_photon_map()->get_max_photons());

      ne = ne + 1;
    }

    world->get_photon_map()->scale_photon_power(1/world->get_photon_map()->getPhotonCount());
    world->get_photon_map()->balance();
}

