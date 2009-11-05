#include "CGLA/Vec3f.h"
#include <iostream>
#include <fstream>
#include "BMesh/obj_load.h"

using namespace std;
using namespace CGLA;

/*****

Rudimentary support for obj files. This really needs work. Presently,
only geometry is loaded!

*/

namespace BMesh
{
	bool parse_line()
	{
		return false;
	}

	bool obj_load(const std::string& filename, Object& obj)
	{
		ifstream ifi(filename.data());
		const int BUFSIZE=1024;
		char buffer[BUFSIZE];
		
		TriMesh* mesh =  obj.create_mesh();

		while(!ifi.eof())
			{
				ifi.getline(buffer, BUFSIZE);
				char *data;
				int n = strcspn(buffer, " ");
				data = buffer + n+1;
				buffer[n] = '\0';
				switch(buffer[0])
					{
					case '#':
						{
							cout << "comment" << endl;
						}
						break;
					case 'f':
						{
							Face vert_id, tvert_id, norm_id;
							int vert_id4[4];
							if(9==sscanf(data, "%d/%d/%d %d/%d/%d %d/%d/%d",
												&vert_id[0], &tvert_id[0], &norm_id[0],
												&vert_id[1], &tvert_id[1], &norm_id[1],
												&vert_id[2], &tvert_id[2], &norm_id[2]))
								{
									mesh->add_face(vert_id-Vec3i(1));
									//bmesh->addCFace(vert_id-Vec3i(1));
								}
							else if(sscanf(data, "%d %d %d %d", &vert_id4[0], 
														 &vert_id4[1],  &vert_id4[2], &vert_id4[3])==4)
								{
									mesh->add_face(Face(vert_id4[0]-1,vert_id4[1]-1,
																			vert_id4[2]-1));
									mesh->add_face(Face(vert_id4[0]-1,vert_id4[2]-1,
																			vert_id4[3]-1));
								}
							else if(sscanf(data, "%d %d %d", &vert_id[0], 
														 &vert_id[1],  &vert_id[2]))
								{
									mesh->add_face(vert_id-Vec3i(1));
								}
						}
						break;
					case 'v':
						{
							if(!strcmp(buffer,"v"))
								{
									Vertex v;
									sscanf(data, "%f %f %f", &v[0], &v[1], &v[2]);
									mesh->add_vertex(v);
								}
//  							else if(!strcmp(buffer,"vt"))
//  								{
// 									// So we use texture coords as colour vertices
//  									Vec3f v;
//  									sscanf(data, "%f %f %f", &v[0], &v[1], &v[2]);
//  									bmesh->addCVertex(v);
// 									//cout << v << endl;
//  								}
// 							else if(!strcmp(buffer,"vn"))
// 								{
// 									Vec3f v;
// 									sscanf(data, "%f %f %f", &v[0], &v[1], &v[2]);
// 									bmesh->normals->t_verts.push_back(v);
// 								}
						}
						break;
					case 'g':
						{
							cout << "group " << data << endl;
						}
						break;
					case 'o':
						{
							cout << "object " << data << endl;
						}
						break;
					}
			}
		return true;
	}

}
