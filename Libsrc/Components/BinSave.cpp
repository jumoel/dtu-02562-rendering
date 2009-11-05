#include <assert.h>
#include "BinSave.h"

namespace Components
{
	using namespace std;

	ostream& bsave_string(ostream& os,const string& s)
	{
		int i = s.length();
		if(i==0)
			os.write((char*)&i, sizeof(int));
		else
			{
				++i;
				os.write((char*) &i, sizeof(int));
				os.write(s.c_str(), i);		
			}
		return os;
	}

	istream& bload_string(istream& is,string& s)
	{
		int i;
		is.read((char*) &i, sizeof(int));
		assert(i>=0);
		if(i>0)
			{
				char *cstr = new char[i+1];
				is.read((char*) cstr, i);
				s = string(cstr);
				delete [] cstr;
			}
		return is;
	}


}
