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
		std::map<int, ItemInfo> items;

		bool LoadXMLInfo();
	};
}

#endif