#include "X3DSceneGraph/SceneGraph.h"
#include <CGLA/Vec3f.h>

using namespace std;
using namespace CGLA;

namespace X3DSceneGraph
{
 
	extern bool materialenable;
	int alltris=0;

	Vertex::Vertex() {
		count = 0;
	}

	void Face::calculateNormal() {
		Vec3f vec1 = vertex[1]->position-vertex[0]->position;
		Vec3f vec2 = vertex[2]->position-vertex[1]->position;
		normal = cross(vec1,vec2);
		normal.normalize();
	
		vertex[0]->normal = (vertex[0]->normal*vertex[0]->count + normal)/(vertex[0]->count + 1);
		vertex[0]->normal.normalize();
		vertex[0]->count++;
	
		vertex[1]->normal = (vertex[1]->normal*vertex[1]->count + normal)/(vertex[1]->count + 1);
		vertex[1]->normal.normalize();
		vertex[1]->count++;
	
		vertex[2]->normal = (vertex[2]->normal*vertex[2]->count + normal)/(vertex[2]->count + 1);
		vertex[2]->normal.normalize();
		vertex[2]->count++;

		d=dot(normal,vertex[1]->position);

	}

	Face::Face() {
		vertex[0] = 0;
		vertex[1] = 0;
		vertex[2] = 0;
	}


	IndexedFaceSet::IndexedFaceSet() {
		coord=0;
		texCoord=0;
		normal=0;
		normalPerVertex=false;
		dirty=true;
	}

	void IndexedFaceSet::init() {
		createFaceSet();
	}

	void IndexedFaceSet::draw() {
		if (SG_DEBUG)
			cout << "IndexedFaceSet" << endl;
		if ((*pAppearance)!=0 && materialenable) {
			(*pAppearance)->apply();
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		}
		if (!dirty) {
			glCallList(theset);
		} else {
			dirty=false;
			theset=glGenLists(1);
			glNewList(theset,GL_COMPILE);
		
			for(vector<Face*>::iterator p = faces.begin();p != faces.end();++p) {
				glBegin(GL_POLYGON);
				if (creaseAngle<0.1) // This is a hack - should be calculated better
					glNormal3f((*p)->normal[0],(*p)->normal[1],(*p)->normal[2]); // Only use thsi if normal pr. face
			
				for (int i=0;i<(*p)->vertex_count;i++) {
					if ((*p)->texCoordIndices[i]!=-1) {
						glTexCoord2f(texCoord->point[(*p)->texCoordIndices[i]][0] * (*pAppearance)->texture->factorx, texCoord->point[(*p)->texCoordIndices[i]][1] * (*pAppearance)->texture->factory); 
					}
					if (creaseAngle>0.1) // This is a hack - should be calculated better
						glNormal3f((*p)->vertex[i]->normal[0],(*p)->vertex[i]->normal[1],(*p)->vertex[i]->normal[2]);
					glVertex3f((*p)->vertex[i]->position[0],(*p)->vertex[i]->position[1],(*p)->vertex[i]->position[2]);
				}
				glEnd();
			}
			glEndList();
		}
		if ((*pAppearance)!=0 && materialenable) {
			(*pAppearance)->unApply();
		}
	}

	void IndexedFaceSet::endFace(Face *face) {
		face->normal=-cross(face->vertex[0]->position-face->vertex[1]->position,face->vertex[2]->position-face->vertex[1]->position);
		face->normal.normalize();
		face->d=-dot(face->normal,face->vertex[1]->position);
	}

	void IndexedFaceSet::createFaceSet() {
		int k;
		for(k=0;k<coord->point.size();k++) {
			Vertex* vertex = new Vertex();
			vertex->position=coord->point[k];
			vertices.push_back(vertex);
		}

		vector<int>::iterator j=texCoordIndex.begin();
		Face* face = 0;
		int nr=0;
		for(vector<int>::iterator i=coordIndex.begin();i!=coordIndex.end();++i) {
			if ((*i)==-1) {
				face->calculateNormal();
				face->vertex_count = nr;
				nr=0;
			} else {
				switch (nr) {
				case 0:
					face=new Face();
					faces.push_back(face);
					face->vertex[0]=vertices[*i];
					nr++;
					break;
				default:
					face->vertex[nr++]=vertices[*i];
				
					break;
				}
				if (j!=texCoordIndex.end()) // Only set texture coordinate if a texture coordinate exists
					face->texCoordIndices[nr-1]=(*j);
				else
					face->texCoordIndices[nr-1]=-1;
			}
			if (j!=texCoordIndex.end()) // Only increment texture thing if there actually is a texture
				j++;
		}
	}

	void IndexedFaceSet::updateBV() {
	
		for(int k=0;k<coord->point.size();k++) {
			float r = coord->point[k].length();
			if (r>bv.radius)
				bv.radius =  r;
			for(int i=0;i<3;i++) {
				if (coord->point[k][i]<bv.aabb.min[i])
					bv.aabb.min[i]=coord->point[k][i];
				if (coord->point[k][i]>bv.aabb.max[i])
					bv.aabb.max[i]=coord->point[k][i];
			}
		}
	}

}
