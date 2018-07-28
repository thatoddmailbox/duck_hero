#ifndef _SAVE_MANAGER_HPP
#define _SAVE_MANAGER_HPP

#include <string>

#include "external/pugixml.hpp"

#include "level.hpp"

namespace duckhero
{
	class SaveManager
	{
	public:
		static std::string GetPathForSlot(int slot_index);
		static void LoadFromFile(std::string path, Level * l);
		static void SaveToFile(std::string path, Level * l);
	};
}

#endif