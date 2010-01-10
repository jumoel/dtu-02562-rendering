#include <cstdlib>  // For random number generator
#include <ctime>    // For time function

#include "AreaLightSource.h"
#include "World.h"

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