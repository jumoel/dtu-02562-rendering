#include "Parse.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;
using namespace CGLA;

namespace
{
	const char seps[]   = " ,\t\n";

	inline char* next_etoken(const char* btoken)
	{
		return const_cast<char*>(btoken)+strcspn(btoken, seps);
	}
	
	inline const char* next_btoken(char* etoken)
	{
		return const_cast<const char*>(etoken+strspn(etoken, seps));
	}
}

namespace Components {
	string floatToString(float value) {
		stringstream ret;
		string stringret;
		ret << value;
		getline(ret,stringret);
		return stringret;
	}

	void parse(const char* str,bool& x) {
#ifdef _MSC_VER
    	x = !(stricmp(str,"true"));
#else
		x = !(strcasecmp(str,"true"));
#endif
	}

	void parse(const char* str,string& x) {
		x=string(str);
	}

	void parse(const char* str,int& x) {
		/* Establish string and get the first token: */
		char *etoken=0;
		x = strtol(str,0,10);
	} 

	void parse(const char* str,Vec2i& vec)
	{   /* Establish string and get the first token: */
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken=next_etoken(btoken);
		vec[0] = strtol(btoken,0,10);
		btoken= next_btoken(etoken);
		etoken= next_etoken(btoken);
		vec[1] = strtol(btoken,0,10);
	}


	void parse(const char* str,float& x) 
	{
		/* Establish string and get the first token: */
		char *etoken=0;
		x = strtod(str,0);
	}

	void parse(const char* str,Vec2f& vec) {
		const char seps[]   = " ,\t\n";
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken= next_etoken(btoken);
		vec[0] = strtod(btoken,0);
		btoken=next_btoken(etoken);
		etoken=next_etoken(btoken);
		vec[1] = strtod(btoken,0);
	}

	void parse(const char* str,Vec3f& vec) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken= next_etoken(btoken);
		vec[0] = strtod(btoken,0);
		btoken=next_btoken(etoken);
		etoken=next_etoken(btoken);
		vec[1] = strtod(btoken,0);
		btoken=next_btoken(etoken);
		etoken=next_etoken(btoken);
		vec[2] = strtod(btoken,0);
	}


	void parse(const char* str,Vec4f& vec) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken= next_etoken(btoken);
		vec[0] = strtod(btoken,0);
		btoken=next_btoken(etoken);
		etoken=next_etoken(btoken);
		vec[1] = strtod(btoken,0);
		btoken=next_btoken(etoken);
		etoken=next_etoken(btoken);
		vec[2] = strtod(btoken,0);
		btoken=next_btoken(etoken);
		etoken=next_etoken(btoken);
		vec[3] = strtod(btoken,0);
	}

	void parse(const char* str,vector<float>& v) {
		const char seps[]   = " ,\t\n";
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken= next_etoken(btoken);
		while(etoken>btoken)
		{
			v.push_back(strtod(btoken,0));
			btoken=next_btoken(etoken);
			etoken=next_etoken(btoken);
		}
	}

	void parse(const char* str,vector<Vec2f>& v) {
		const char seps[]   = " ,\t\n";
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken= next_etoken(btoken);
		while(etoken>btoken)
		{
			Vec2f vec;
			vec[0] = strtod(btoken,0);
			btoken=next_btoken(etoken);
			etoken=next_etoken(btoken);
			vec[1] = strtod(btoken,0);
			btoken=next_btoken(etoken);
			etoken=next_etoken(btoken);
			v.push_back(vec);
		}
	}

	void parse(const char* str,vector<Vec3f>& v) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken= next_etoken(btoken);
		while(etoken>btoken)
		{
			Vec3f vec;
			vec[0] = strtod(btoken,0);
			btoken=next_btoken(etoken);
			etoken=next_etoken(btoken);
			vec[1] = strtod(btoken,0);
			btoken=next_btoken(etoken);
			etoken=next_etoken(btoken);
			vec[2] = strtod(btoken,0);
			btoken=next_btoken(etoken);
			etoken=next_etoken(btoken);
			v.push_back(vec);
		}
	}

	void parse(const char* str,vector<int>& v) 
	{
		const char seps[]   = " ,\t\n";
		const char *btoken=next_btoken(const_cast<char*>(str));
		char *etoken= next_etoken(btoken);
		while(etoken>btoken)
			{
				v.push_back(strtol(btoken,0,10));
				btoken=next_btoken(etoken);
				etoken=next_etoken(btoken);
			}
	}
	
}
