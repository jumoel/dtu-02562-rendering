#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include "RenderEngine.h"
#include "Canvas.h"
#include "Graphics/PPMBitmap.h"
#include <iostream>



using namespace std;
using namespace GFX;

const Vec3f RenderEngine::trace_ray(const Vec2f& pi)
{
	Vec2f p = canvas->window_coords2image_coords(pi);
	Vec3f r_dir = normalize(camera->get_ray_direction(p));
	Ray r(camera->get_position(),r_dir);
  r.set_first();
	return world->shade_ray(r);
}

bool RenderEngine::render_some(int pixels)
{
	static int x=0;
	for (int y=0;y<canvas->get_height(); ++y)
		{
			Vec3f col = trace_ray(Vec2f(x,y));
			
			// Simply clamp colours with too high intensity
			col = v_min(Vec3f(1,1,1), col);

			// Gamma correct - crude tone mapping
			col[0] = pow(col[0], 1.0f/2.5f);
			col[1] = pow(col[1], 1.0f/2.5f);
			col[2] = pow(col[2], 1.0f/2.5f);

			canvas->draw_pixel(x,y, col);
		}
	if(++x == canvas->get_width())
		{
			x=0;
			return true;
		}
	return false;
}
