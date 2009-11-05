#ifndef __CONVERTTOOL_H__
#define __CONVERTTOOL_H__

#include "DataFormat.h"
#include "X3DSceneGraph/SceneGraph.h"
#include <vector>

namespace  X3DSceneGraph {
  void convertToNewFormat(X3DSceneGraph::Group* group, std::vector<MyVertex*> *vertices, std::vector<MyPolygon*> *polygons);
}

#endif // __CONVERTTOOL_H__
