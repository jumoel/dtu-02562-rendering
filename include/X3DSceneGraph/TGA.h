#ifndef __TGA_H__
#define __TGA_H__

namespace X3DSceneGraph
{

	enum tga_type 
		{ 
			TGA24=0, 
			TGA32, 
			TGARLE24
		};

	class TargaImage
	{
	public:
		// data
		int *m_pImage;
		// constructors
		TargaImage();
		~TargaImage();
		// data
		int m_iWidth, m_iHeight;
		// methods
		void read(const char *file, tga_type t);
		void read_normal24(const char *name);
		void read_normal32(const char *name);
		void read_rle24(const char *name);
		void write(const char *file, tga_type t);
		void write_normal24(const char *name);
		void write_normal32(const char *name);
		void write_rle24(const char *name);
	};

}
namespace SG = X3DSceneGraph;

#endif

