#include "X3DSceneGraph/ImageLoader.h"
#include "X3DSceneGraph/TGA.h"

using namespace std;

namespace X3DSceneGraph
{

	bool loadHeights(std::string filename, std::vector<float> *plane) {
		string s = filename.substr(filename.size()-4,4); // contains the suffix of the filename
		TargaImage p; 
		if (s==".tga") {
			p.read(filename.c_str(),TGA32);
			for (int i=0;i<p.m_iHeight;i++)
				for (int j=0;j<p.m_iWidth;j++) {
					int c = p.m_pImage[i*p.m_iWidth+j];
					int r =(c >> 8) & 0xff;
					int g =(c >> 16) & 0xff;
					int b =(c >> 24) & 0xff;
					int a =c & 0xff;
					plane->push_back((float)r*0.5f);
				}
			return true;
		} 
		return false;
	}
}
