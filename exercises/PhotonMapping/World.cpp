#include "Common/CommonDefs.h"
#include "World.h"
#include "PhotonMap.h"

using namespace CGLA;
using namespace CMN;
using namespace std;

float World::first_intersection(Ray& ray)
{

	for(int i=0;i<object_list.size(); ++i)
		object_list[i]->intersect(ray);
	return ray.get_parameter();
}

CGLA::Vec3f World::shade_ray(Ray& r)
{
	Vec3f col = trace(r);
	return col;
}

CGLA::Vec3f World::trace(Ray& ray)
{
  if (ray.get_level() > MAX_RECURSION_DEPTH)
    return background;

	first_intersection(ray);
	if (ray.did_hit())
		return (ray.intersected())->shade(ray);
	// Return the background color.
	return background;
}

void World::direct_light(const Ray& incident,const CGLA::Vec3f& norm, 
												 std::vector<LightSample>& samples)
{

}

/*
PHOTON MAPPING
*/
void World::trace_photon(Ray &ray, CGLA::Vec3f power)
{
  if (ray.get_level() > MAX_RECURSION_DEPTH)
    return;

  first_intersection(ray);
  if (ray.did_hit()) {
    (ray.intersected())->trace_photon(ray, power);
  }
}