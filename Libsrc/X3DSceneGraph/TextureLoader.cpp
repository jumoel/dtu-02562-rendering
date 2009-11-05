#pragma warning(disable:4244)   // No warnings on precision truncation
#pragma warning(disable:4305)   // No warnings on precision truncation
#pragma warning(disable:4786)   // stupid symbol size limitation


#include "X3DSceneGraph/TextureLoader.h"
#include "X3DSceneGraph/TGA.h"

#include <vector>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

namespace X3DSceneGraph
{

	std::string TextureLoaderPath;

	void TextureLoader::load(string filename, bool mipmap) {
		string s;
		filename =TextureLoaderPath + filename;
		s = filename.substr(filename.size()-4,4);
		if (s==".tga") {
			TargaImage p; 

			p.read(filename.c_str(),TGA32);
			load_size_x = p.m_iWidth;
			load_size_y = p.m_iHeight;
			int i,j;
			for (i=2;i<=4096 /*Max texture size*/;i*=2) 
				if (i>=load_size_x) 
					break;
			size_x = i;
			for (i=2;i<=4096 /*Max texture size*/;i*=2) 
				if (i>=load_size_y) 
					break;
			size_y = i;
			int mipmap_factor=1;
			if (mipmap)
				mipmap_factor=2; // Maybe to large??

			vector<unsigned char> image(size_x*size_y*4*2);
			for(i=0;i<load_size_y;i++)
				for(j=0;j<load_size_x;j++) {
					int c = p.m_pImage[i*load_size_x+j];
					image[((load_size_y-i-1)*size_x+j)*4+1]=(c >> 8) & 0xff;
					image[((load_size_y-i-1)*size_x+j)*4+0]=(c >> 16) & 0xff;
					image[((load_size_y-i-1)*size_x+j)*4+3]=(c >> 24) & 0xff;
					image[((load_size_y-i-1)*size_x+j)*4+2]=c & 0xff;
				}
			/*			if (mipmap)
							gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, size_x, 
							size_y, GL_RGBA, GL_UNSIGNED_BYTE, 
							static_cast<void*>(&image[0]));

							glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size_x, 
							size_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
							static_cast<void*>(&image[0])); 
			*/
		} 
	}
}
