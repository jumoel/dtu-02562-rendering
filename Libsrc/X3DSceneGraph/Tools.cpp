#include "X3DSceneGraph/Tools.h"

using namespace std;
using namespace CGLA;

namespace X3DSceneGraph 
{
	string floatToString(float value) {
		stringstream ret;
		string stringret;
		ret << value;
		getline(ret,stringret);
		return stringret;
	}

	void parseBool(const char* str,bool *x) {
		if (strcmp(str,"true")==0)
			*x=true;
		else
			*x=false;
	}

	void parseString(const char* str,string *x) {
		string mystr(str);
		*x=mystr;
	}

	void parse1i(const char* str,int *x) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		char *token;
		token = strtok( (char *)str, seps );
		*x = atoi(token);
	}

	void parse1f(const char* str,float *x) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		char *token;
		token = strtok( (char *)str, seps );
		*x = atof(token);
	}

	void parse2f(const char* str,float *x, float *y) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		char *token;
		token = strtok( (char *)str, seps );
		*x = atof(token); token = strtok( NULL, seps );
		*y = atof(token); 
	}

	void parse3f(const char* str,float *x, float *y, float *z) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		char *token;
		token = strtok( (char *)str, seps );
		*x = atof(token); token = strtok( NULL, seps );
		*y = atof(token); token = strtok( NULL, seps );
		*z = atof(token); 
	}

	void parse4f(const char* str,float *x, float *y, float *z, float *a) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		char *token;
		token = strtok( (char *)str, seps );
		*x = atof(token); token = strtok( NULL, seps );
		*y = atof(token); token = strtok( NULL, seps );
		*z = atof(token); token = strtok( NULL, seps );
		*a = atof(token); 
	}

	void parsexf(const char* str,vector<float> *v) {
		const char seps[]   = " ,\t\n";
		char *token;
		token = strtok( (char *)str, seps );
		while( token != NULL )
		{
			(*v).push_back(atof(token)); 
			token = strtok( NULL, seps );
		}
	}

	void parsex2f(const char* str,vector<Vec2f> *v) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		char *token;
		Vec2f *vec;
		token = strtok( (char *)str, seps );
		while( token != NULL )
		{
			vec=new Vec2f();
      /* While there are tokens in "string" */
			(*vec)[0] = atof(token); token = strtok( NULL, seps );
			(*vec)[1] = atof(token); token = strtok( NULL, seps );
			(*v).push_back(*vec);
		}
	}

	void parsex3f(const char* str,vector<Vec3f> *v) {
   /* Establish string and get the first token: */
		const char seps[]   = " ,\t\n";
		char *token;
		Vec3f *vec;
		token = strtok( (char *)str, seps );
		while( token != NULL )
		{
			vec=new Vec3f();
      /* While there are tokens in "string" */
			(*vec)[0] = atof(token); token = strtok( NULL, seps );
			(*vec)[1] = atof(token); token = strtok( NULL, seps );
			(*vec)[2] = atof(token); token = strtok( NULL, seps );
			(*v).push_back(*vec);
		}
	}

	void parsexi(const char* str,vector<int> *v) {
		const char seps[]   = " ,\t\n";
		char *token;
		token = strtok( (char *)str, seps );
		while( token != NULL )
		{
			(*v).push_back(atoi(token)); 
			token = strtok( NULL, seps );
		}
	}
}
