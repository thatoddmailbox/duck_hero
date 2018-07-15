#ifndef _SHOP_HPP
#define _SHOP_HPP

#include <cstdlib>
#include <string>
#include <vector>

#include "physfs.h"

#include "external/pugixml.hpp"

namespace duckhero
{
	struct ShopItem
	{
		int item_id;
		int price;
	};

	class Shop
	{
	public:
		std::string name;
		std::vector<ShopItem> items;

		bool LoadXMLInfo(std::string path);
	};
}

#endif