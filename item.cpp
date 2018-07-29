#include "item.hpp"

namespace duckhero
{
	Item::Item(int new_id)
	{
		id = new_id;
	}

	bool Item::operator==(Item &other)
	{
		return (id == other.id);
	}

	bool Item::operator==(const Item &other)
	{
		return (id == other.id);
	}
}