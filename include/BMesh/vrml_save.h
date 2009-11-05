#ifndef __VRML_SAVE_H__
#define __VRML_SAVE_H__

// For now this vrml save function just contains exactly what I need for my current project
#include <string>
#include "Object.h"


namespace BMesh
{
	bool vrml_save(const std::string& filename, Object&);
}

#endif

