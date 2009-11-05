#include <iostream>

#include "BMesh/vrml_save.h"

using namespace std;
using namespace CGLA;

namespace BMesh
{
	bool vrml_save(const string& filename, Object &obj) {
		FILE *stream;
		int i,j;
		stream = fopen(filename.data(), "wb");
		if(!stream) {
			cout << "Error - file could not be written" << endl;
			return false;
		}
		fprintf(stream, "#VRML V2.0 utf8\n\n");
		fprintf(stream, "Transform {\n");
		fprintf(stream, " children [\n");
		
		for(i=0;i<obj.no_meshes();i++) {
			fprintf(stream, "  Shape {\n");
			fprintf(stream, "   appearance Appearance {\n");
			fprintf(stream, "    material Material {\n");
			fprintf(stream, "     diffuseColor 0.3333 0.1098 0.6941\n");
			fprintf(stream, "    }\n");
			fprintf(stream, "   }\n");
			fprintf(stream, "   geometry IndexedFaceSet {\n");
			// Coordinates
			fprintf(stream, "    coord Coordinate { point [\n");
			TriMesh *mesh = obj.get_mesh(i);
			for(j=0;j<mesh->no_vertices();j++) {
				Vec3f point = mesh->get_vertex(j);
				fprintf(stream, "     %f %f %f\n", point[0], point[1], point[2]);
			}
			fprintf(stream, "    ]}\n");
			// Faces
			fprintf(stream, "    coordIndex [\n");
			for(j=0;j<mesh->no_faces();j++) {
				Face face = mesh->get_face(j);
				fprintf(stream, "     %d %d %d -1\n", face[0], face[1], face[2]);
			}
			fprintf(stream, "    ]\n");
			fprintf(stream, "   }\n");
			fprintf(stream, "  }\n");
		}
		fprintf(stream, " ]\n");
		fprintf(stream, "}\n");
		fclose(stream);
		return true;
	}
}
