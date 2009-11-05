#ifndef __TEXMAP_H__
#define __TEXMAP_H__

#include <CGLA/Vec3f.h>


namespace BMesh
{
	class Texmap {
	public:
		unsigned int id;
		unsigned char *image;
		unsigned int bpp;
		int size_x;
		int size_y;
		int load_size_x;
		int load_size_y;
		char filename[50];

		void load(const char *filename);
		void create_empty_image(int &size_x, int &size_y, int byte_per_pixel);
		void erase();
		void get_value_nearest(const float u, const float v, CGLA::Vec3f &value);
		void get_value_linear(const float u, const float v, CGLA::Vec3f &value);
		void make_checker();
		// Constuctor/destructor
		Texmap();
		~Texmap();
	};

}
#endif



