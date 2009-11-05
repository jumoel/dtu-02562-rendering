#ifndef __PPMBITMAP_H
#define __PPMBITMAP_H

#ifdef __sgi
#include <unistd.h>
#endif

#include <string>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include "Graphics/ColorVector.h"

namespace Graphics
{


	/** An OpenGL compatible bitmap that can be read and written
			as a ppm file */
class PPMBitmap
{
  /// The prefix is in the header when we write the image to disk
  static const char prefixstr[];
  
  /// a pointer to the bitmap
  unsigned char * bitmap;

  /// Size of the image
  int xsz, ysz;

  /** Pobinter to a file to which the image is being written. Used in cases
      where we start writing the image before all pixels are available */
  std::ofstream* bitmap_file;

  /** Used to keep track of how much of the image has been computed */
  long pixel_counter;

  /// Returns a pointer to pixel x, y
  unsigned char* pix(const int x, const int y)
    {
      return &(bitmap[4 * (xsz*y + x)]);
    }

  /// Returns a const pointer to pixel x,y
  const unsigned char* pix(const int x, const int y) const 
    {
      return &(bitmap[4 * (xsz*y + x)]);
    }

public:


  /// Returns a pointer to pixel x, y
  int get_pixel_int(const int x, const int y) const;


  /// Construct bitmap of specified size
  PPMBitmap(const int x, const int y);

  /// Construct and load bitmap from specified file.
  PPMBitmap(const std::string& filename);

  
  /// Destruct Bitmap
  ~PPMBitmap()
    {
      delete bitmap_file;
      delete [] bitmap;
    }

  /// Retrieve width of image
  int  get_width() const {return xsz;}

  /// Retrieve height of image
  int  get_height() const {return ysz;}

  /// Retrieve a pixel as a colour vector.
  ColorVector get_pixel(const int x, const int y) const;

  /// Get a pointer to the bitmap
  void* get() {return bitmap;}

  /// Write the bitmap to disk in one go.
  bool write(const std::string&) const;
  
  /// Assign a colour to a pixel.
  void set_pixel(const int x, const int y, const ColorVector& cv)
    {
      cv.set_PPM_style(pix(x,y));
    }
};

}
namespace GFX = Graphics;

#endif
