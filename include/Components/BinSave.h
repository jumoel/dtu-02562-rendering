#ifndef __BIN_SAVE_H
#define __BIN_SAVE_H

#include <iostream>
#include <vector>
#include <string>

namespace Components
{
	using namespace std;

	template<class T>
	ostream& bsave_simple(ostream& os,const T& t)
	{
		os.write((char*) &t, sizeof(T));
		return os;
	}

	template<class T>
	ostream& bsave_bis(ostream& os,const T& vec)
	{
		int N = vec.size();
		os.write((char*)&N,sizeof(int));
		for(typename T::const_iterator i = vec.begin(); i != vec.end(); i++)
			os.write((char*)&(*i),sizeof(typename T::value_type));
		return os;
	}

	ostream& bsave_string(ostream& os,const string& s);


	template<class T>
	istream& bload_simple(istream& is,T& t)
	{
		is.read((char*) &t, sizeof(T));
		return is;
	}

	template<class T>
	istream& bload_bis(istream& is, T& vec)
	{
		int N;
		is.read((char*)&N,sizeof(int));
		typename T::value_type tmp;
		for(int i=0;i<N;i++)
			{
				is.read((char*)&tmp,sizeof(typename T::value_type));	
				vec.push_back(tmp);
			}
		return is;
	}

	istream& bload_string(istream& is,string& s);
}

namespace CMP = Components;

#endif
