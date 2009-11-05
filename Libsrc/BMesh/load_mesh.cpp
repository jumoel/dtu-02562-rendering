#include <iostream>
#include "BMesh/load_mesh.h"
#include "BMesh/x3d_load.h"
#include "BMesh/obj_load.h"

namespace BMesh
{
	using namespace std;
	bool load_mesh(const std::string& filename, Object& obj)
	{
		if(!filename.compare(filename.size()-4,4,".obj"))
			obj_load(filename, obj);
		else if(!filename.compare(filename.size()-4,4,".x3d"))
			x3d_load(filename, obj);
		else 
			{
				cerr << "Unsupported format" << endl;
				return false;
			}
		return true;
	}

}
