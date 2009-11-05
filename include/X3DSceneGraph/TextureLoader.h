#ifndef __TEXTURELOADER_H__
#define __TEXTURELOADER_H__

#include <string>

namespace X3DSceneGraph
{

	extern std::string TextureLoaderPath;

	class TextureLoader {
	
	public:
		unsigned char *image;
		int size_x;
		int size_y;
		int load_size_x;
		int load_size_y;

		void load(std::string filename, bool mipmap);
	};

}
namespace SG = X3DSceneGraph;

#endif // __TEXTURELOADER_H__
