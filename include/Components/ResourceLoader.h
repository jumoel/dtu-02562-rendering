#ifndef __RESOURCELOADER_H
#define __RESOURCELOADER_H


#include <vector>
#include <string>

namespace Components
{

	class ResourceLoader {
	public:
		std::vector<std::string> names;
		std::vector<std::string> values;

	
		ResourceLoader(const char *filename);

		std::string getString(std::string name);
		int getInt(std::string name);
		float getFloat(std::string name);
	};


}
namespace CMP = Components;

#endif
