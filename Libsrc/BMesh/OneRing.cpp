#include "BMesh/OneRing.h"
#include <algorithm>

using namespace std;
namespace BMesh
{
  OneRing::OneRing(const std::vector<OneRingElement>& _elements):
    elements(_elements)
  {
    int j;
    for(j=0;j<int(elements.size())-1;++j)
      for(int k=j+1;k<elements.size();++k)
	if(elements[j].next_vertex==elements[k].vertex)
	  swap(elements[j+1], elements[k]);
    
    nonborder_manifold = true;
    if(elements.size()==0)
      nonborder_manifold = false;
    else
      for(j=0;j<elements.size();++j)
	{
	  if(elements[j].next_vertex!=elements[(j+1)%elements.size()].vertex)
	    {
	      nonborder_manifold = false;
	      break;
	    }
	}
  }
}

