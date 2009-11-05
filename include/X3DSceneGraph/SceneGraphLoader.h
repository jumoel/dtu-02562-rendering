#ifndef __SCENEGRAPHLOADER_H__
#define __SCENEGRAPHLOADER_H__

#include <expat.h>
#include "SceneGraph.h"

namespace X3DSceneGraph
{
	X3DSceneGraph::Scene* getModel(const char* filename);
	X3DSceneGraph::Scene* getModelFromString(std::string msg);

	void init(X3DSceneGraph::Scene *root);

}
namespace SG = X3DSceneGraph;

#endif // !__SCENEGRAPHLOADER_H__

