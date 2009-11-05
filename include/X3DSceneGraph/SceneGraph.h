#ifndef __SCENEGRAPH_H__
#define __SCENEGRAPH_H__

#ifdef JPEG
#include "imagetype.h"
#include "bitmapimage.h"
#endif

#include <iostream>
#include <vector>
#include <string> 
#include <sstream>

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

#include "CGLA/Vec3f.h"
#include "CGLA/Vec2f.h"
#include "CGLA/Mat4x4f.h"
#include "CGLA/Quaternion.h"
#include <Geometry/Geometry.h>

#define SG_DEBUG 0

namespace X3DSceneGraph {

	const int MAX_POLYGON_SIZE = 4;

	class BoundingVolume {
	public:
		float radius;
		Geometry::AABB aabb;
		BoundingVolume();
	};

	// Class that all that can be drawn inherit from
	class Drawable {
		void *user_data;
	public:
		std::string name;
		BoundingVolume bv;
	
		virtual void draw() = 0;
		virtual void updateBV() = 0;
		// Should have a virtual destructor
		void setUserData(void *);
		void * getUserData();
	};

	// Class that all that can be applied inherit from
	class Applyable {
	public:
		std::string name;
		virtual void apply() = 0;
		virtual void unApply() = 0;
	};

	class Material : public Applyable {
	private:
		GLfloat ambient[4];
		GLfloat diffuse[4];
		GLfloat specular[4];
		GLfloat emission[4];
		GLfloat alpha;
	public:
		GLfloat diffuseColor[3];
		GLfloat ambientIntensity;
		GLfloat specularColor[3];
		GLfloat emissiveColor[3];
		GLfloat shininess;
		GLfloat transparency;
		Material();
		void apply();
		void unApply();
	};

	class Texture {
	public:
		float factorx; //textures must be store in x^2 size textures. factorx/y recalculate to that number
		float factory;

		std::string name;
		GLuint texName;
	};

	class TextureCoordinate {
	public:
		std::vector<CGLA::Vec2f> point;
	};

	class Group : public Drawable {
	public:
		std::vector<Drawable*> children;
		Group *parent;

		Group();
		void addChild(Drawable *Drawable);
		void draw();
		void updateBV();
	};

	class Transform : public Group {
	public:
		CGLA::Vec3f translation;
		CGLA::Quaternion rotation;
		CGLA::Vec3f scale;
		void draw();
		void updateBV();
	};

	class ImageTexture : public Texture {
	private:
		int canvas_width; 
		int canvas_height;
	public:
		std::string url;
		bool repeatS;
		bool repeatT;
		void load();
	};

	class Appearance : public Applyable {
	public:
		Material *material;
		Texture *texture;
		Appearance();
		void apply();
		void unApply();
	};

	class Geometry : public Drawable {
	public:
		Appearance **pAppearance; //Points to the corresponding Appearance
	public:
		virtual void draw() = 0;
		virtual void updateBV() = 0;
	};

	class Normal {
	public:
		std::vector<CGLA::Vec3f> vector;
	};

	class Coordinate {
	public:
		std::vector<CGLA::Vec3f> point;
	};
	/*
		class TextureCoordinate {
		public:
		std::vector<Vec2f> point;
		};
	*/
	class Ray {
	public:
		CGLA::Vec3f point;
		CGLA::Vec3f line;
	};

	class Vertex {
	public:
		//	Vec3f eyeposition; // temp variae transformed into right Coordinate system
		CGLA::Vec3f position;
		CGLA::Vec3f normal;
		int count;
		Vertex();
	};

	class Face {
	public:
		int vertex_count;
		Vertex *vertex[MAX_POLYGON_SIZE];
		int texCoordIndices[MAX_POLYGON_SIZE];
		// Plane equation
		CGLA::Vec3f normal;
		float d;
		// End plane equation
		int neighbourIndices[MAX_POLYGON_SIZE];

		Face();
		void calculateNormal();
	};

	// IndexedFaceSet
	class Sphere : public Geometry {
	public:
		float radius;
		void draw();
		void init();
		void updateBV();

		Sphere();
	};

	// IndexedFaceSet
	class IndexedFaceSet : public Geometry {
	private:
		GLuint theset; 
		bool dirty; // has the vertices been touched since last draw
	public: // 

		std::vector<Face*> faces;
		std::vector<Vertex*> vertices;
		void createFaceSet();
		void findNeighbourIndices();
		void debug();
		void endFace(Face *face);

	public:
		Coordinate* coord;
		std::vector<int> coordIndex;
		TextureCoordinate* texCoord;
		std::vector<int>  texCoordIndex;
		/*	Color* color;
				std::vector<int> colorIndex;*/
		Normal* normal;
		std::vector<int>  normalIndex;
		bool normalPerVertex;
		float creaseAngle;

		IndexedFaceSet();
		void draw();
		void init();
		void updateBV();
	};

	class Shape : public Drawable {
	public:
		Appearance *appearance;
		Geometry *geometry;
		Shape();
		void draw();
		void updateBV();
	};

	class Scene : public Group {
	private:
		Material* material;
	public:
		Scene();
		void init();
		void draw();
		void updateBV();
		void enableMaterial(bool value);
	};
}


namespace SG = X3DSceneGraph;

#endif // !__SCENEGRAPH_H__
