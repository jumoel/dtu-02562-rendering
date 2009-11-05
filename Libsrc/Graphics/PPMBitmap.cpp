#include <assert.h>
#include <fstream>

#include "PPMBitmap.h"

namespace Graphics
{

	const char PPMBitmap::prefixstr[] = "P6\n# GK incorporated \n%d %d\n255\n";

	using namespace std;

	PPMBitmap::PPMBitmap(const int x, const int y):
		xsz(x), ysz(y), bitmap_file(0), pixel_counter(0)
	{
		bitmap = new unsigned char[4*xsz*ysz];
		if(!bitmap)
			{
				cerr << "could not allocate bitmap" << endl;
				exit(1);
			}
	}

	PPMBitmap::PPMBitmap(const std::string& filename)
		:bitmap_file(0), pixel_counter(0)
	{
		fstream f(filename.c_str(), ios::in | ios::binary );
	
		if (!f)
			{
				cerr << "Couldn't open file"  << filename << endl; 
				exit(1);
			}
		else
			{
				char c;
				while(f.read(&c,1) && c!= 0x0a);
			
				// Read comments
				while(f.read(&c,1) && c == '#')
					while(f.read(&c,1) && c!= 0x0a);
      
				// Read size
				char sizestr[80] = {c,'\0'};
				int i = 1;
				while(f.read(sizestr + i,1) && sizestr[i++] != 0x0a);

				// Scan x,y size
				sscanf(sizestr,"%d %d", &xsz, &ysz);

				if (xsz == 0 || ysz == 0)
					{
						cerr << "Bad image file header" << endl;
						exit(1);
					}

				while(f.read(&c,1) && c!= 0x0a);  // read till newline

				// Allocate bitmap 
				bitmap = new unsigned char[4*xsz*ysz];
			
				assert(bitmap);	
			
				//read the pixels and put them in bitmap
				for(int y= 0; y<ysz; y++)
					for(int x= 0; x<xsz; x++)
						{
							unsigned char pixels[4]= {0,0,0,255};
							f.read((char*)pixels, 3);
							memcpy(pix(x,ysz-y-1), pixels, 4);
						}
			}
	}

	ColorVector PPMBitmap::get_pixel(const int x, const int y) const
	{
		double red, green, blue;

		red   = double(*(pix(x,y)))  / 255.0;
		green = double(*(pix(x,y)+1)) / 255.0;
		blue  = double(*(pix(x,y)+2)) / 255.0;

		return ColorVector(red, green ,blue);
	}

	int PPMBitmap::get_pixel_int(const int x, const int y) const 
	{
		union { int int_val ; unsigned char ubyte_val[4];  };
		ubyte_val[0] = bitmap[4 * (xsz*y + x)];
		ubyte_val[1] = bitmap[4 * (xsz*y + x)+1];
		ubyte_val[2] = bitmap[4 * (xsz*y + x)+2];
		ubyte_val[3] = bitmap[4 * (xsz*y + x)+3];
		return int_val;
	}


  
	bool PPMBitmap::write(const string& filename) const
	{
		fstream f(filename.c_str(),ios::out|ios::binary);
		if(f.good())
			{
				char str[80];
				char *bitmap_ptr = (char*)(bitmap);
				sprintf(str, prefixstr, xsz, ysz);
				f.write(str, strlen(str));
				for(int j=ysz-1; j>=0; j--)
					for(int i=0; i<xsz; i++)
						f.write(&(bitmap_ptr[(j*xsz+i)*4]), 3);
				f.close();
				return true;
			}
		return false;
	}

}

