#include <assert.h>
#include "ZlibBinSave.h"

namespace Components
{
	using namespace std;

	void bsave_string(gzFile os,const string& s)
	{
		int i = s.length();
		if(i==0)
			gzwrite(os, (void*)&i, sizeof(int));
		else
			{
				++i;
				gzwrite(os, (void*) &i, sizeof(int));
				gzwrite(os, (void*) s.c_str(), i);		
			}
	}

	void bload_string(gzFile is,string& s)
	{
		int i;
		gzread(is, (void*) &i, sizeof(int));
		assert(i>=0);
		if(i>0)
			{
				char *cstr = new char[i+1];
				gzread(is, (void*) cstr, i);
				s = string(cstr);
				delete cstr;
			}
	}


}
