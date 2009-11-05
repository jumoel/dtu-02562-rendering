#ifndef __POINTDB_H
#define __POINTDB_H
// Author: J. Andreas Bærentzen,
// Created: Wed Feb 20 11:02:5

#include "CGLA/Vec3f.h"
#include <vector>
#include <utility>
#include <stack>

namespace Components
{
	
	/** 
	*/	
	template<class D>
	class VectorDB
	{
		/// A vec of vecs of points 
		std::vector<D> data;

		/// A stack containing free indices.
		std::stack<int> free_indices;
	public:

		/// Get a reference to an entry
		D& get(int i) {return data[i];}

		/// Const - get a reference to an entry
		const D& get(int i) const {return data[i];}

		/// Add entry to the db
		int add();

		/// Recycle an entry
		void recycle(int i);

		int size() const {return data.size();}
	};

	template<class D>
	inline int VectorDB<D>::add()
	{
		if(free_indices.empty())
			{
				data.push_back(D());
				return data.size()-1;
			}
		int i = free_indices.top();
		free_indices.pop();
		return i;
	}

	template<class D>
	inline void VectorDB<D>::recycle(int i)
	{
		data[i] = D();
		free_indices.push(i);
	}

}

namespace CMP      = Components;
#endif
