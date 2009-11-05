// This file was written by Theo Engel-Nielsen

#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <assert.h>

#include "X3DSceneGraph/TGA.h"

using namespace std;

namespace X3DSceneGraph
{

	TargaImage::TargaImage()
	{
		m_pImage = NULL;
		m_iWidth=0;
		m_iHeight=0;
	};

	TargaImage::~TargaImage()
	{
		if (m_pImage!=NULL)
			free(m_pImage);
	}

	void TargaImage::read(const char *filename, tga_type t)
	{
		switch(t)
			{
			case TGA24:
				read_normal24(filename);
				break;
			case TGA32:
				read_normal32(filename);
				break;
			case TGARLE24:
				read_rle24(filename);
				break;
			}
	}

	void TargaImage::write(const char *filename, tga_type t)
	{
		switch(t)
			{
			case TGA24:
				write_normal24(filename);
				break;
			case TGA32:
				write_normal32(filename);
				break;
			case TGARLE24:
				write_rle24(filename);
				break;
			}
	}

	void TargaImage::read_normal24(const char *filename)
	{
		// loads the background image for clearbackground()
		// the image must be TGA - 24 bit, 8bpp, uncompressed
    ifstream os(filename,ios::in|ios::binary);
    if (!os) { cout << "could not open image '"<<filename<<"' file for reading" << endl; assert(0) ; exit(-1); }

    unsigned char header[64];
    os.read((char*)header,18);
	
		m_iWidth =  header[12] + (header[13]<<8);
		m_iHeight = header[14] + (header[15]<<8);

		if (m_pImage!=NULL) free(m_pImage);
		m_pImage=(int*)malloc(m_iWidth*m_iHeight*sizeof(int));
		if (m_pImage==NULL)
			{
				cout << "Could not allocate memory for file:" << filename << " - ERROR" << endl;
				os.close();
				return;
			}

		for (int y=m_iHeight-1; y>=0; y--)
			{
				//os.read((char*)&lock[width*y*3],width*3);
				for (int x=0; x<m_iWidth; x++)
					{
						int rgb=0;
						os.read((char*)&rgb,3);
						*(m_pImage+x+y*m_iWidth) = rgb;
					}
			}
		os.close();
	}

	void TargaImage::read_normal32(const char *filename)
	{
		// loads the background image for clearbackground()
		// the image must be TGA - 24 bit, 8bpp, uncompressed
    ifstream os(filename,ios::in|ios::binary);
    if (!os) { cout << "could not open image '"<<filename<<"' file for reading" << endl; assert(0) ; exit(-1); }

    unsigned char header[64];
    os.read((char*)header,18);
	
		m_iWidth =  header[12] + (header[13]<<8);
		m_iHeight = header[14] + (header[15]<<8);

		if (m_pImage!=NULL) free(m_pImage);
		m_pImage=(int*)malloc(m_iWidth*m_iHeight*sizeof(int));
		if (m_pImage==NULL)
			{
				cout << "Could not allocate memory for file:" << filename << " - ERROR" << endl;
				os.close();
				return;
			}  

		for (int y=m_iHeight-1; y>=0; y--)
			{
				for (int x=0; x<m_iWidth; x++)
					{
						int argb=0;
						os.read((char*)&argb,4);
						*(m_pImage+x+y*m_iWidth) = argb;
					}
			}
		os.close();
	}

	void TargaImage::read_rle24(const char *filename)
	{
		ifstream os(filename,ios::in|ios::binary);
		if (!os) { 
			cout << "could not open image '"<<filename<<"' file for reading" << endl; 
			exit(-1); 
		}

		unsigned char header[18];

		os.read((char*)header,18);
    m_iWidth =  header[12] + (header[13]<<8);
    m_iHeight = header[14] + (header[15]<<8);

		if (m_pImage!=NULL) free(m_pImage);
		m_pImage=(int*)malloc(m_iWidth*m_iHeight*sizeof(int));
		if (m_pImage==NULL)
			{
				cout << "Could not allocate memory for file:" << filename << " - ERROR" << endl;
				os.close();
				return;
			}

		for(int y=m_iHeight; y>=0; y--)
			for(int x=0; x<m_iWidth; )
				{
					unsigned char rep;
					int rgb=0;
					os.read((char*)&rep,1);
					if (rep>=128)
						{
							// decode RLE chunk
							rep = (rep&127)+1;
							os.read((char*)&rgb,3);
							for(int rx=0; rx<rep; rx++)
								*(m_pImage+x+rx+y*m_iWidth) = rgb;
							x+=(int)rep;
						}
					else
						{
							rep++;
							// decode dump chunk
							for(int rx=0; rx<rep; rx++)
								{
									os.read((char*)&rgb,3);
									*(m_pImage+x+rx+y*m_iWidth) = rgb;
								}
							x+=(int)rep;
						}
				}
		os.close();
	}

	void TargaImage::write_normal24(const char *filename)
	{
		// write a TGA file of the console
		// format is 24 bits, 8bpp, uncompressed
    ofstream os(filename,ios::out|ios::binary);
    if (!os) 
			{ 
				cout << "could not open image '"<<filename<<"' file for writing" << endl; 
				exit(-1); 
			}
    unsigned char header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    header[12] = m_iWidth & 0xFF;
    header[13] = m_iWidth >> 8;
    header[14] = m_iHeight & 0xFF;
    header[15] = m_iHeight >> 8;
    header[16] = 24;
    os.write((char*)header,18);
    for (int y=m_iHeight-1; y>=0; y--) 
	    for(int x=0; x<m_iWidth; x++)
				os.write((char*)&m_pImage[m_iWidth*y+x],3);
		os.close();
	}

	void TargaImage::write_normal32(const char *filename)
	{
		// write a TGA file of the console
		// format is 32 bits, 8bpp, uncompressed
    ofstream os(filename,ios::out|ios::binary);
    if (!os) 
			{ 
				cout << "could not open image '"<<filename<<"' file for writing" << endl; 
				exit(-1); 
			}
    unsigned char header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    header[12] = m_iWidth & 0xFF;
    header[13] = m_iWidth >> 8;
    header[14] = m_iHeight & 0xFF;
    header[15] = m_iHeight >> 8;
    header[16] = 32;
    os.write((char*)header,18);
    for (int y=m_iHeight-1; y>=0; y--) 
	    for(int x=0; x<m_iWidth; x++)
				os.write((char*)&m_pImage[m_iWidth*y+x],4);
		os.close();
	}


	void TargaImage::write_rle24(const char *filename)
	{
		FILE *f;

		if ((f=fopen(filename,"wb"))==NULL)
			{ 
				cout << "could not open image '"<<filename<<"' file for writing" << endl; 
				exit(-1); 
			}

		int iDepth = 32;
		int iAlpha = 8;

		fwrite("\000\000\012\000\000\000\000\000\000\000\000\000",1,12,f);
		fwrite(&m_iWidth,1,2,f);
		fwrite(&m_iHeight,1,2,f);
		fwrite(&iDepth,1,1,f);
		fwrite(&iAlpha,1,1,f);

		// no image identification field data (length=0)
		// no colour map data (length=0)

		for (int y=m_iHeight-1; y>=0; y--)
			{
				int buf[128];
				int x,i;
				for (x=0; x<m_iWidth; )
					{
						for (i=0; x<m_iWidth && i<128 && m_pImage[y*m_iWidth+x]!=m_pImage[y*m_iWidth+x+1]; x++,i++)
							buf[i] = *(m_pImage+y*m_iWidth+x);
						if (i>0)
							{
								int tmp = i-1;
								fwrite(&tmp,1,1,f);
								fwrite(buf,4,i,f);
							}
						for (i=0; x<m_iWidth && i<128 && m_pImage[y*m_iWidth+x]==m_pImage[y*m_iWidth+x+1]; x++,i++);
						if (i>0)
							{
								int tmp = (i-1)|128;
								fwrite(&tmp,1,1,f);
								fwrite(m_pImage+y*m_iWidth+x,4,1,f);
							}
					}
			}

		fprintf(f,"TRUEVISION-XFILE.");
		fclose(f);
	}
}
