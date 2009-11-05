#ifndef __LOADER_H__
#define __LOADER_H__

#include <string>

// This is just an example of a loader
#include "Object.h"

namespace BMesh
{

	bool load_mesh(const std::string& filename, Object&);

}
#endif
