#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "ResourceLoader.h"
#include "expat.h"

#include <functional>

using namespace std;

namespace Components
{

	void startElement(void *userData, const char *name, const char **atts) {
		ResourceLoader* rl = static_cast<ResourceLoader*>(userData); 
		int j=0;
		if (strcmp(name,"Values")==0) {  // Values
			while (atts[j]!=0) {
				rl->names.push_back(string(atts[j++]));
				rl->values.push_back(string(atts[j++]));
			}
		} 		
	}

	void endElement(void *userData, const char *name) {
	}

		
	ResourceLoader::ResourceLoader(const char *filename) {
		const int BUF_SIZE = 10000;
		char buf2[BUF_SIZE];
		//Load Scene 
		XML_Parser parser = XML_ParserCreate(NULL);
		int done=0;
		XML_SetElementHandler(parser, startElement, endElement);
		XML_SetUserData(parser, this);  
		FILE *in;             /* file pointer */

		if ((in=fopen(filename,"r"))==NULL) {
			cout << "Error. resource file not found" << endl;
		}

		size_t len;
		do {
			len = fread(buf2,1,BUF_SIZE,in);
			if (len!=BUF_SIZE)
				done=1;
			if (!XML_Parse(parser, buf2, len, done)) {
				fprintf(stderr,
								"%s at line %d\n",
								XML_ErrorString(XML_GetErrorCode(parser)),
								XML_GetCurrentLineNumber(parser));
				return;
			}
		} while (!done);
		fclose(in);
		XML_ParserFree(parser);
		return;
	}

	string ResourceLoader::getString(string name) {
		for (int i=0;i<names.size();i++) {
			if (name==names[i])
				return values[i];
		}
		return string("");
	}

	int ResourceLoader::getInt(string name) {
		int res = 0;
		stringstream mystrstr;
		for (int i=0;i<names.size();i++) {
			if (name==names[i]) {
				mystrstr << values[i];
				mystrstr >> res;
				return res;
			}
		}
		return 0;
	}

	float ResourceLoader::getFloat(string name) {
		float res = 0;
		stringstream mystrstr;
		for (int i=0;i<names.size();i++) {
			if (name==names[i]) {
				mystrstr << values[i];
				mystrstr >> res;
				return res;
			}
		}
		return 0.0f;
	}

}

namespace CMP = Components;
