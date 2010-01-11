#ifndef __AREALIGHTSOURCE_H
#define __AREALIGHTSOURCE_H

#include "LightSource.h"

/** AreaLightSource class. Behaviour is only defined for square surfaces. */
class AreaLightSource : public LightSource
{
private:
	CGLA::Vec3f *position;
  CGLA::Vec3f normal;
  float s;
  float t;

  int num_samples;

  int current_sample;

public:

	AreaLightSource(World* _world, CGLA::Vec3f corners[4], int numsamples, const CGLA::Vec3f& ints) : 
        LightSource(_world,ints),
        position(corners),
        num_samples(numsamples)
  {
    normal = CGLA::cross(position[1] - position[0], position[2] - position[0]);
    normal.normalize();

    s = 0.0;
    t = 0.0;
  }
  
	CGLA::Vec3f get_position();
  CGLA::Vec3f get_normal() const {
    return normal;
  }
  void emit_photons();

  int get_no_samples() const {return (num_samples + 1) * (num_samples + 1);}
		
	bool is_point_source() const {return false;}
};

#endif