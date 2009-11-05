#ifndef __OBJLOAD_H__
#define __OBJLOAD_H__

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

	bool obj_load(const std::string& filename, Object&);

}
#endif
