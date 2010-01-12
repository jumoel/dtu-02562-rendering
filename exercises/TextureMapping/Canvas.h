#ifndef __CANVAS_H
#define __CANVAS_H

#include <map>

#include "Common/CommonDefs.h"
#include "CGLA/Vec2f.h"
#include "Graphics/ColorVector.h"
#include "Graphics/PPMBitmap.h"

/** A render canvas for bitmaps. I.e. rgb values with a byte per 
		value. 
*/

class Canvas
{
	/// Actual Bitmap containing image
  GFX::PPMBitmap bitmap;

	/// Width and height of canvas
  int width, height;

	/// Half width and height of canvas.
  float xw2,yw2;

	/// Texture used for OpenGL rendering.
	int tex_no;

public:
	/// Constructs a canvas with specified dimensions
	Canvas(int w, int h, int _tex_no): 
		width(w), height(h), bitmap(w,h), tex_no(_tex_no)
	{
		xw2 = width / 2.0f;
		yw2 = height / 2.0f;
	}

	/// Returns width of canvas
	int get_width() const {return width;}

	/// Returns height of canvas
	int get_height() const {return height;}
  
	/** 2D transform from window coordinates to image coordinates.
			Image coordinates are in the [-1,1]x[-1,1] range */
	const CGLA::Vec2f window_coords2image_coords(const CGLA::Vec2f& p)
	{
		return (p-CGLA::Vec2f(xw2,yw2))/CGLA::Vec2f(width,height);
	}
       
	/// Draw a pixel to the canvas.
	void draw_pixel(int x, int y, const GFX::ColorVector& cv)
	{
		bitmap.set_pixel(x, y, cv);
	}

	void write(const std::string& name) const
	{
		bitmap.write(name);
	}

	/// Update OpenGL texture. Used for incremental updating of windows.
	void update_texture()
	{
		glBindTexture(GL_TEXTURE_2D, tex_no);
		// Why do we need GL_RGBA8 below and not just GL_RGBA. 
		// Apparently the ATI driver has a stupid default value.
		glTexImage2D(GL_TEXTURE_2D,  0, GL_RGBA8, 
								 width, height, 0, GL_RGBA,
								 GL_UNSIGNED_BYTE,  bitmap.get());
	}
};
#endif


