#ifndef __SCENEGRAPHTOOLS_H__
#define __SCENEGRAPHTOOLS_H__

#include "SceneGraph.h"

namespace X3DSceneGraph
{

	typedef bool (*traverse_callback)(X3DSceneGraph::Drawable*);

	void calculateAABB(X3DSceneGraph::IndexedFaceSet *faceset, CGLA::Vec3f* min, CGLA::Vec3f * max);
	void calculateAABB(X3DSceneGraph::Group *group, CGLA::Vec3f* min, CGLA::Vec3f * max);
	X3DSceneGraph::Drawable* findObject(std::string name, X3DSceneGraph::Group* group);
	void traverse(X3DSceneGraph::Group *group, traverse_callback callback);

}
namespace SG = X3DSceneGraph;

#endif // __SCENEGRAPHTOOLS_H__

