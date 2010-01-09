#ifndef _RENDERENGINE__H
#define _RENDERENGINE__H

#include <time.h>

#include "CGLA/Vec3f.h"
#include "Canvas.h"
#include "World.h"
#include "Camera.h"

using namespace CGLA;
using namespace CMN;

/** The RenderEngine Contains the main loop of the program.
		RenderEngine ties together the World (containing all objects and lights),
		the camera and the canvas (unto which pixels are drawn). */
class RenderEngine
{
	/// World (containing all objects and lights),
	World *world;
	
	/// canvas (unto which pixels are drawn).
	Canvas* canvas;

	/// Viewing information.
	Camera* camera;

	/// Trace a single ray
	const Vec3f trace_ray(const Vec2f& pi);
		
public:

	/** Build engine from world information, a canvas and a camera. */
 	RenderEngine(World*  _world, 
	 						 Canvas* _canvas,
							 Camera* _camera): 
 		world(_world), canvas(_canvas), camera(_camera)
	{
		srand((unsigned)time(0));	
	}
	
	bool render_some(int);

};

#endif

