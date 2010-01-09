#ifndef __WORLD_H
#define __WORLD_H

#include <list>
#include <vector>
#include <assert.h>
#include "Object3D.h"
#include "LightSource.h"
#include "PhotonMap.h"

typedef std::vector<Object3D*>::iterator    Object3DPtrIterator;
typedef std::vector<LightSource*>::iterator LightSourcePtrIterator;

/** class World. World contains global information about the scene.
		In particular World contains a list of lights and objects. However, World 
		also contains other information and function that can be used to trace
		a ray into the World (and get a colour back). World also contains functions
		useful for photon mapped caustics. */
class World
{
	/// List of all objects in our world
  std::vector<Object3D*>    object_list;

	/// List of all lightsources in world
  std::vector<LightSource*> light_source_list;
  
	/// Photon map storing photons used for caustics.
	Photon_map caustic_photons;

	/// Ambient colour
	CGLA::Vec3f ambient;

	/** Background colour used to shade rays that miss all objects and 
			continue into the void. */
	CGLA::Vec3f background;

public:
  
	World():
		object_list(0), light_source_list(0),
		caustic_photons(10000)
	{};

	/// Set & get ambient level
	void set_ambient(const CGLA::Vec3f& amb) { ambient = amb;}
	CGLA::Vec3f get_ambient() { return ambient;}

	/// Set & get background color.
	void set_background(const CGLA::Vec3f bkg) { background = bkg;}
	CGLA::Vec3f get_background() {return background;}

	/// Add a light source to our World
	void add_light(LightSource* ls) 
	{
		light_source_list.push_back(ls);
	};

  Photon_map* get_photon_map() {
    return &caustic_photons;
  }

	/* Get the list of lights in the world
	 */
	const std::vector<LightSource*>& get_light() {
	  return light_source_list;
	}
  
	/// Add an object to our world
	void add_object(Object3D* o3d)
	{
		object_list.push_back(o3d);
	}

	/// Return the object that first intersects `ray'
	float first_intersection(Ray& ray);

	/// Shade a ray
	CGLA::Vec3f shade_ray(Ray& ray);

	/// Recursively trace a ray into the world
	CGLA::Vec3f trace(Ray& ray);

  /// Recursively trace a photon into the world
  void trace_photon(Ray &ray, CGLA::Vec3f power);

	/** Direct illumination. This function creates a set of samples from
			light sources. Tests visibility using shadow rays. */
	void direct_light(const Ray&, const CGLA::Vec3f&,
										std::vector<LightSample>&);
		
    
};
#endif




