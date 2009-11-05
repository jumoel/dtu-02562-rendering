#include <iostream>
#include <fstream>
#include <stdio.h>

#include "X3DSceneGraph/Tools.h"
#include "X3DSceneGraph/SceneGraph.h"
#include "X3DSceneGraph/SceneGraphLoader.h"

using namespace std;
using namespace CGLA;

namespace X3DSceneGraph
{
	Scene *root;
	Group *curroot; 

	Shape *shape;
	IndexedFaceSet *indexedFaceSet;
	Appearance *appearance;
	vector<ImageTexture *> loaders;

	void startElement(void *userData, const char *name, const char **atts)
	{
		int j=0;
		float x,y,z,a;
		if (strcmp(name,"Scene")==0) {  // Scene
			root = new Scene();
			curroot=static_cast<Group*>(root);
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&root->name); }
				j++;
			}
		} else if (strcmp(name,"Group")==0) {  // Group
			Group *group = new Group();
			curroot->addChild(group);
			group->parent=curroot;
			curroot=group;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&group->name);}
				j++;
			}
		} else if (strcmp(name,"Transform")==0) {  // Transform
			Transform *transform = new Transform();
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&transform->name);
				} else if (strcmp(atts[j],"translation")==0) { parse3f(atts[++j], &x, &y, &z);	transform->translation.set(x,y,z);
				} else if (strcmp(atts[j],"rotation")==0) { parse4f(atts[++j], &x, &y, &z, &a); transform->rotation.make_rot(a,Vec3f(x,y,z));
				} else if (strcmp(atts[j],"scale")==0) { parse3f(atts[++j], &x, &y, &z); transform->scale.set(x,y,z);
				}
				j++;
			}
			curroot->addChild(transform);
			transform->parent=curroot;
			curroot=transform;
		} else if (strcmp(name,"Shape")==0) { // Shape
			shape = new Shape();
			curroot->addChild(shape);
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&shape->name);}
				j++;
			}
		} else if (strcmp(name,"Appearance")==0) { // Appearance
			assert(shape!=0);
			appearance = new Appearance();
			shape->appearance=appearance;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&appearance->name);}
				j++;
			}
		} else if (strcmp(name,"IndexedFaceSet")==0) {  // IndexedFaceSet
			assert(shape!=0);
			indexedFaceSet = new IndexedFaceSet();
			shape->geometry=indexedFaceSet;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&indexedFaceSet->name);
				} else if (strcmp(atts[j],"coordIndex")==0) { parsexi(atts[++j],&indexedFaceSet->coordIndex);
				} else if (strcmp(atts[j],"normalIndex")==0) { parsexi(atts[++j],&indexedFaceSet->normalIndex);
				} else if (strcmp(atts[j],"texCoordIndex")==0) { parsexi(atts[++j],&indexedFaceSet->texCoordIndex);
				} else if (strcmp(atts[j],"creaseAngle")==0) { parse1f(atts[++j],&indexedFaceSet->creaseAngle);
//				} else if (strcmp(atts[j],"castshadow")==0) { parseBool(atts[++j],&indexedFaceSet->castshadow);
				}
				j++;
			}
		} else if (strcmp(name,"Sphere")==0) {  // Sphere
			assert(shape!=0);
			Sphere *sphere = new Sphere();
			shape->geometry=sphere;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&sphere->name);
				} else if (strcmp(atts[j],"radius")==0) { parse1f(atts[++j],&sphere->radius);
				}
				j++;
			}
		} else if (strcmp(name,"ImageTexture")==0) {  // ImageTexture
			assert(appearance!=0);
 			ImageTexture *imageTexture = new ImageTexture();
			appearance->texture=imageTexture;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&imageTexture->name);
				} else if (strcmp(atts[j],"repeatS")==0) { parseBool(atts[++j],&imageTexture->repeatS);			
				} else if (strcmp(atts[j],"repeatT")==0) { parseBool(atts[++j],&imageTexture->repeatT);			
				} else if (strcmp(atts[j],"url")==0) { parseString(atts[++j],&imageTexture->url);			
				}
				j++;
			}
			loaders.push_back(imageTexture);
		} else if (strcmp(name,"Coordinate")==0) {  // Coordinate
			assert(indexedFaceSet!=0);
			Coordinate *coordinate = new Coordinate();
			indexedFaceSet->coord = coordinate;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"point")==0) { 
					parsex3f(atts[++j],&coordinate->point);
				} 
				j++;
			}
		} else if (strcmp(name,"Normal")==0) {  // Normal
			assert(indexedFaceSet!=0);
			Normal *normal = new Normal();
			indexedFaceSet->normal=normal;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"vector")==0) { 
					parsex3f(atts[++j],&normal->vector);
				} 
				j++;
			}
		} else if (strcmp(name,"Material")==0) {  // Material
			assert(appearance!=0);
			Material *material = new Material();
			appearance->material=material;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"DEF")==0) { parseString(atts[++j],&material->name);
				} else if (strcmp(atts[j],"diffuseColor")==0) { parse3f(atts[++j],&material->diffuseColor[0], &material->diffuseColor[1], &material->diffuseColor[2]);
				} else if (strcmp(atts[j],"ambientIntensity")==0) { parse1f(atts[++j],&material->ambientIntensity);
				} else if (strcmp(atts[j],"specularColor")==0) { parse3f(atts[++j],&material->specularColor[0], &material->specularColor[1], &material->specularColor[2]);
				} else if (strcmp(atts[j],"emissiveColor")==0) { parse3f(atts[++j],&material->emissiveColor[0], &material->emissiveColor[1], &material->emissiveColor[2]);
				} else if (strcmp(atts[j],"shininess")==0) { parse1f(atts[++j],&material->shininess);
				} else if (strcmp(atts[j],"transparency")==0) { parse1f(atts[++j],&material->transparency);
				} 
				j++;
			}
		} else if (strcmp(name,"TextureCoordinate")==0) {  // TextureCoordinate
			assert(indexedFaceSet!=0);
			TextureCoordinate *textureCoordinate = new TextureCoordinate();
			indexedFaceSet->texCoord=textureCoordinate;
			while (atts[j]!=0) {
				if (strcmp(atts[j],"point")==0) { 
					parsex2f(atts[++j],&textureCoordinate->point);
				} 
				j++;
			}
		} 
	}

	void endElement(void *userData, const char *name)
	{
	/*	if (strcmp(name,"Scene")==0) 
			root->init();*/
		if (strcmp(name,"Group")==0 || strcmp(name,"Transform")==0) {
			curroot=curroot->parent;
		}
		if (strcmp(name,"Shape")==0) 
			shape=0;
		if (strcmp(name,"IndexedFaceSet")==0) {
			indexedFaceSet->init();
			indexedFaceSet=0;
		}
		if (strcmp(name,"Appearance")==0) 
			appearance=0;
	}

	Scene* getModelFromString(string s) {
	  XML_Parser parser = XML_ParserCreate(NULL);
		XML_SetElementHandler(parser, startElement, endElement);
		if (!XML_Parse(parser, s.c_str(), s.length(), true)) {
		  fprintf(stderr,
			  "%s at line %d\n",
			  XML_ErrorString(XML_GetErrorCode(parser)),
			  XML_GetCurrentLineNumber(parser));
		  return root;
		}
	  XML_ParserFree(parser);
		init(root);
	  return root;
	}

	Scene* getModel(const char* filename) {
		const int BUF_SIZE = 10000;
	  char buf2[BUF_SIZE];
	  //Load Scene 
	  XML_Parser parser = XML_ParserCreate(NULL);
	  int done=0;
		curroot=0;
		XML_SetElementHandler(parser, startElement, endElement);

    FILE *in;             /* file pointer */

		if ((in=fopen(filename,"r"))==NULL) {
			cout << "Error. X3D filename not found:" << filename << endl;
			assert (0 && "X3D filename not found:" );
			return root;
		}

		size_t len;
		do {
			len = fread(buf2,1,BUF_SIZE,in);
			if (len!=BUF_SIZE)
				done=1;
		if (!XML_Parse(parser, buf2, len, done)) {
		  fprintf(stderr,
			  "%s at line %d\n",
			  XML_ErrorString(XML_GetErrorCode(parser)),
			  XML_GetCurrentLineNumber(parser));
		  return root;
		}
	  } while (!done);
		fclose(in);
	  XML_ParserFree(parser);
	  return root;
	}

	void init(Scene *root) {
		vector<ImageTexture *>::iterator i = loaders.begin();
		while (i!=loaders.end()) {
			(*i)->load();
			i++;
		}
		loaders.clear();
		root->init();
	}
}
