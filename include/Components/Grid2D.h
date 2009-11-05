#ifndef __GRID2D_H
#define __GRID2D_H

#include <vector>
namespace Components
{

	template<class T>
	class Grid2D
	{
		int XDIM, YDIM;
		std::vector<T> pixels;

	public:
		
		Grid2D(int i, int j, const T& val): XDIM(i), YDIM(j), pixels(i*j, val) {}
		Grid2D(int i, int j): XDIM(i), YDIM(j), pixels(i*j) {}
		
		const T& operator()(int i, int j) const 
		{
			return pixels[j*XDIM+i];
		}

		T& operator()(int i, int j) 
		{
			return pixels[j*XDIM+i];
		}

		int get_xdim() const {return XDIM;}
		int get_ydim() const {return YDIM;}
		
	};
}
namespace CMP = Components;
#endif
