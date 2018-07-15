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
	};

	struct ItemInfo
	{
		int id;
		std::string name;
		std::string desc;
	};
}

#endif