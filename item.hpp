#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <string>

namespace duckhero
{
	class Item
	{
	public:
		int id;

		Item(int new_id);
		bool operator==(Item &other);
		bool operator==(const Item &other);
	};

	struct ItemInfo
	{
		int id;
		std::string name;
		std::string desc;
	};
}

#endif