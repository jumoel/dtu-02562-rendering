#ifndef __LIGHTSOURCE_H
#define __LIGHTSOURCE_H

#include <vector>
#include "CGLA/Vec3f.h"

class World;
class Object3D;
 
/** The LightSample class contains very basic information about a light source
		that has been hit by a shadow ray - i.e. is not occluded. 
		Basically just the direction to the light source, the distance and 
		the amount of light. */
struct LightSample 
{
	CGLA::Vec3f dir;
	float dist;
	CGLA::Vec3f irradiance;
};


/** The abstract LightSource is the ancestor of all other light source classes.
		*/
class LightSource 
{
protected:
	World* world;
	CGLA::Vec3f intensities;
public:

	LightSource(World* _world,
							const CGLA::Vec3f& _intensities):
		world(_world), 
		intensities(_intensities) {}
		 
	/// Return the position of the light source
	virtual CGLA::Vec3f get_position() const = 0;

	/** Get the normal to the light source. This only makes sense for 
	non point light sources. */
	virtual CGLA::Vec3f get_normal() const = 0;
	
	/** Get the intensity of the light source. This is really the total emitted
			power - so one should be careful to divide by the number of samples in
			case of area lights */
	CGLA::Vec3f get_intensities() const {return intensities;}
	
	/** Number of samples to cast from a given point towards the light source. */
	virtual int get_no_samples() const {return 1;}

  virtual void emit_photons() {};

};

#endif 


