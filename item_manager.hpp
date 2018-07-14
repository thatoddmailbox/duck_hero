#ifndef _ITEM_MANAGER_HPP
#define _ITEM_MANAGER_HPP

#include <cstdlib>
#include <map>
#include <string>
#include <vector>

#include "physfs.h"

#include "external/pugixml.hpp"

#include "item.hpp"

namespace duckhero
{
	class ItemManager
	{
	public:
		static std::map<int, ItemInfo> items;

		static bool LoadXMLInfo();
	};
}

#endif