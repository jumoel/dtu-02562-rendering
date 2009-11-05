#include <iostream>
#include "BMesh/AdjFaceList.h"

using namespace std;
using namespace CGLA;

namespace BMesh
{

	struct PolygonList {
		vector<int> p_list;
	};



	AdjFaceList::AdjFaceList(TriMesh& mesh):
		adjfaces(mesh.no_faces())
	{
		int i;
		int facecount = mesh.no_faces();

		vector<PolygonList> my_list;
		my_list.resize(mesh.no_vertices());
	
		for(i=0;i<facecount;i++) 
			{
				for(int j=0;j<3;j++) 
					my_list[mesh.get_face(i)[j]].p_list.push_back(i);
			}
		for(i=0;i<facecount;i++) 
			{
				AdjFace aface;
				for(int j=0;j<3;j++) 
					{

						aface.f[j]=static_cast<unsigned int>(-1);
						int first_index = mesh.get_face(i)[j];
						int next_index = mesh.get_face(i)[(j+1)%3];
						// Find all triangles that has this index
						for(int k=0;k<my_list[first_index].p_list.size();k++) {
							// In each of these triangles see whether
							// they have a right neighbor
							int triangle_id = my_list[first_index].p_list[k];
							if (triangle_id==i)
								continue;
							for(int l=0;l<3;l++) 
								{
									int f_index = mesh.get_face(triangle_id)[l];
									int n_index = mesh.get_face(triangle_id)[(l+2)%3];
									if (f_index==first_index && n_index==next_index) 
										{
											aface.f[j]=triangle_id;
											break;
										}
								}
						}
					}
				adjfaces[i]=aface;
			}
	}
}
	
