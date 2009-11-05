#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <string>
#include <sstream>
#include <vector>
#include <CGLA/Vec3f.h>
#include <CGLA/Vec2f.h>

namespace X3DSceneGraph
{
	std::string floatToString(float value);
	void parseBool(const char* str,bool *x);
	void parseString(const char* str,std::string *x);
	void parse1i(const char* str,int *x);
	void parse1f(const char* str,float *x);
	void parse2f(const char* str,float *x, float *y);
	void parse3f(const char* str,float *x, float *y, float *z);
	void parse4f(const char* str,float *x, float *y, float *z, float *a);
	void parsexf(const char* str,std::vector<float> *v);
	void parsex2f(const char* str,std::vector<CGLA::Vec2f> *v);
	void parsex3f(const char* str,std::vector<CGLA::Vec3f> *v);
	void parsexi(const char* str,std::vector<int> *v);

}
namespace SG = X3DSceneGraph;

#endif // __TOOLS_H__
