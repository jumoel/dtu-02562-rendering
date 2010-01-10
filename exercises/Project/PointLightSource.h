#ifndef __POINTLIGHTSOURCE_H
#define __POINTLIGHTSOURCE_H

#include "LightSource.h"

/** PointLightSource class represents a single point sending light equally
		in all directions. */
class PointLightSource : public LightSource
{
	CGLA::Vec3f position;

public:

	PointLightSource(World* _world,
									 const CGLA::Vec3f& pos,
									 const CGLA::Vec3f& ints): 
		LightSource(_world,ints),	position(pos) {}
  
	CGLA::Vec3f get_position() const {return position;}
	CGLA::Vec3f get_normal() const 
	{
		assert(0);
		return CGLA::Vec3f(1,1,1);
	}
		
	bool is_point_source() const {return true;}

  void emit_photons();
};

#endif