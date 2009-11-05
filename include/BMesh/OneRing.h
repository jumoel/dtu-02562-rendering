#ifndef __ONERING_H__
#define __ONERING_H__

#include "TriMesh.h"

namespace BMesh
{

	struct OneRingElement
	{
		int face;
		int vertex;
		int next_vertex;
	};


	class OneRing
	{
		std::vector<OneRingElement> elements;
		bool nonborder_manifold;
	public:

		OneRing(const std::vector<OneRingElement>& _elements);
	
		int valency() const {return elements.size();}

		int get_face(int i) const {return elements[i].face;}

		int get_vertex(int i) const {return elements[i].vertex;}

		int get_next_vertex(int i) const {return elements[i].vertex;}

		bool is_nonborder_manifold() const {return nonborder_manifold;}
	};

}
#endif
