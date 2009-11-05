#ifndef __BIN_SAVE_H
#define __BIN_SAVE_H

#include <zlib.h>
#include <vector>
#include <string>

namespace Components
{
	using namespace std;

	template<class T>
	void zsave_simple(gzFile os,const T& t)
	{
		gzwrite(os, (void*) &t, sizeof(T));
	}

	template<class T>
	void zsave_bis(gzFile os,const T& vec)
	{
		int N = vec.size();
		gzwrite(os, (void*)&N,sizeof(int));
		for(typename T::const_iterator i = vec.begin(); i != vec.end(); i++)
			gzwrite(os,(void*)(&(*i)),sizeof(typename T::value_type));
	}

	void zsave_string(gzFile os,const string& s);

	template<class T>
	void zload_simple(gzFile is,T& t)
	{
		gzread(is, (void*) &t, sizeof(T));
	}

	template<class T>
	void zload_bis(gzFile is, T& vec)
	{
		int N;
		gzread(is, (void*)&N,sizeof(int));
		typename T::value_type tmp;
		for(int i=0;i<N;i++)
			{
				gzread(is, (void*)(&tmp),sizeof(typename T::value_type));	
				vec.push_back(tmp);
			}
	}

	void zload_string(gzFile,string&);
}
namespace CMP = Components;

#endif
