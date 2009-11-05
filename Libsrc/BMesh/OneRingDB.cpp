#pragma warning (disable : 4786) 
#include "BMesh/OneRingDB.h"

using namespace std;
namespace BMesh
{
	OneRingDB::OneRingDB(const TriMesh& mesh)
	{
		int i;
		std::vector<std::vector<OneRingElement> > elems(mesh.no_vertices());
		for(i=0;i<mesh.no_faces();++i)
			{
				const Face& f = mesh.get_face(i);
				for(int j=0;j<3;++j)
					{
						OneRingElement e;
						e.face = i;
						e.vertex = f[(j+1)%3];
						e.next_vertex = f[(j+2)%3];
						elems[f[j]].push_back(e);
					}
			}
		for(i=0;i<mesh.no_vertices(); ++i)
			one_rings.push_back(OneRing(elems[i]));
	}
}
