#ifndef __X3DLOAD_H__
#define __X3DLOAD_H__

#include <string>

// This is just an example of a loader
#include "Object.h"

#ifdef WIN32
#include "expat/expat.h"
#else
#include "expat.h"
#endif


namespace BMesh
{

	bool x3d_load(const std::string& filename, Object&);

}
#endif
