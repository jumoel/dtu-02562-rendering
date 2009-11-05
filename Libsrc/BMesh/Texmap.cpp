#include <assert.h>
#include <stdio.h>
#ifdef WIN32
#include <io.h>
#endif
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <CGLA/Vec2i.h>
#include <CGLA/Vec2f.h>
#include "BMesh/Texmap.h"

//#define USE_DEVIL

#ifdef USE_DEVIL
#include <IL/il.h>
#include <IL/ilu.h>
#endif

using namespace std;
using namespace CGLA;

namespace BMesh
{
	Texmap::Texmap() {
		image = 0;
		bpp = 0;
		size_x = 0;
		size_y = 0;
		load_size_x = 0;
		load_size_y = 0;
	}

	Texmap::~Texmap() {
		if (image!=0)
			delete image;
	}

	void Texmap::erase() {
		if (image!=0)
			delete image;
		image = 0;
		bpp = 0;
		size_x = 0;
		size_y = 0;
		load_size_x = 0;
		load_size_y = 0;
	}

	void Texmap::get_value_nearest(const float u, const float v, Vec3f &value) {
		if (u==1)
			int i=3*3;
		float fx = u*(float)size_x;
		float fy = v*(float)size_y;
		int x = static_cast<int>(fx);
		int y = static_cast<int>(fy);
		int bits = bpp/8;
		value[0] = image[(y*size_x+x)*bits + 0];
		value[1] = image[(y*size_x+x)*bits + 1];
		value[2] = image[(y*size_x+x)*bits + 2];
		value/=256;
	}

	void Texmap::get_value_linear(const float u, const float v, Vec3f &value) {
		assert (u>=0 && u<=1);
		assert (v>=0 && v<=1);
 	
		float fx = u*(float)(size_x)-0.5;
		float fy = v*(float)(size_y)-0.5;
		int bits = bpp/8;

		// Find the four nearest corners
		Vec2i min_val=Vec2i(s_max((float)floor(fx),0.0f),
												s_max((float)floor(fy),0.0f));
		Vec2i max_val=Vec2i(s_min((float)ceil(fx),(float)(size_x-1)) ,
												s_min((float)ceil(fy),(float)(size_y-1)));

		int c1_index = (min_val[1]*size_x+min_val[0])*bits;
		int c2_index = (min_val[1]*size_x+max_val[0])*bits;
		int c3_index = (max_val[1]*size_x+max_val[0])*bits;
		int c4_index = (max_val[1]*size_x+min_val[0])*bits;

		Vec3f c1 = Vec3f(image[c1_index], image[c1_index+1], image[c1_index+2]);
		Vec3f c2 = Vec3f(image[c2_index], image[c2_index+1], image[c2_index+2]);
		Vec3f c3 = Vec3f(image[c3_index], image[c3_index+1], image[c3_index+2]);
		Vec3f c4 = Vec3f(image[c4_index], image[c4_index+1], image[c4_index+2]);

		Vec2f pos = Vec2f(fx-min_val[0],fy-min_val[1]);

		// Find the weights that these corners should be weighted with

		// Make bilinear interpolation
		Vec3f inter1 = c1*(1.-pos[0]) + c2*pos[0];
		Vec3f inter2 = c4*(1.-pos[0]) + c3*pos[0];
		value = inter1*(1-pos[1]) + inter2*pos[1];

		value/=256;
	}

	void Texmap::load(const char *_filename) {
#ifdef USE_DEVIL
		strcpy(filename, _filename);
		char ext[4];
		char fnc[80];
		unsigned int len = strlen(filename);
		strcpy(fnc, filename);
		strncpy(ext,&filename[len-3],3);
		ext[3]='\0';
		int id = 1;

		ILenum Error;
		ILuint  ImgId;

		static bool washere = false;
		if(!washere)
			{
				ilInit();
				iluInit();
				washere=true;
			}
		ilEnable(IL_CONV_PAL);
		ilGenImages(1, &ImgId);
		ilBindImage(ImgId);
		if(!ilLoadImage(filename))
			{
				cout << "could not load " << filename << endl;
				exit(0);
			}

		load_size_x = ilGetInteger(IL_IMAGE_WIDTH);
		load_size_y = ilGetInteger(IL_IMAGE_HEIGHT);
		bpp = ilGetInteger(IL_IMAGE_BITS_PER_PIXEL);
		
		if (bpp==24)
			ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		else if (bpp==32)
			ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		else if (bpp==8)
			ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
		else 
			assert(0);

		int i;
		for (i=2;i<=4096 ;i*=2) 
			if (i>=load_size_x) 
				break;
		size_x = i;
		for (i=2;i<=4096 ;i*=2) 
			if (i>=load_size_y) 
				break;
		size_y = i;
		
		if(size_x != load_size_x || size_y != load_size_y)
			{
				iluImageParameter(ILU_FILTER, ILU_BILINEAR);
				iluScale(size_x, size_y, 1);
			}

		const int image_size =size_x*size_y*ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
		image = new unsigned char[image_size];
		memcpy(image, ilGetData(), image_size);
		ilDeleteImages(1, &ImgId);
		
		while ((Error = ilGetError())) {
			cout << __LINE__ << "Error: " << iluErrorString(Error) << endl;
		}
#endif
	}
	
	float log2(float val) {
		return log(val)/log(2.0f);
	}

	void Texmap::create_empty_image(int &_size_x, int &_size_y, int byte_per_pixel) {
		size_x = pow(2.0f,ceil(log2((float)(_size_x))));
		size_y = pow(2.0f,ceil(log2((float)(_size_y))));
		size_x = s_max(size_x,2); // Because of error on ATI graphics card
		size_y = s_max(size_y,2); // Because of error on ATI graphics card
		_size_x = size_x;
		_size_y = size_y;
		image = new unsigned char[size_x*size_y*byte_per_pixel];
		load_size_x = size_x;
		load_size_y = size_y;
		bpp = byte_per_pixel*8;
	}
	void Texmap::make_checker() {
		int k = bpp/8;
		int i, j, c;
		for (i = 0; i < size_x; i++) {
			for (j = 0; j < size_y; j++) {
				c = ((((i&0x1)==0)^((j&0x1))==0))*255;
				image[(i+j*size_x)*k+0] = c;
				image[(i+j*size_x)*k+1] = c;
				image[(i+j*size_x)*k+2] = c;
			}
		}
	}
}	
