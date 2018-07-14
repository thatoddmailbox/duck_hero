#include "item_manager.hpp"

namespace duckhero
{
	std::map<int, ItemInfo> ItemManager::items = std::map<int, ItemInfo>();

	bool ItemManager::LoadXMLInfo()
	{
		// read the file into a string
		PHYSFS_File * f = PHYSFS_openRead("items.xml");
		PHYSFS_sint64 size = PHYSFS_fileLength(f);
		char * buffer = (char *) malloc(size + 1);
		buffer[size] = '\0';
		PHYSFS_readBytes(f, buffer, size);
		PHYSFS_close(f);

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_string(buffer);

		bool return_value = true;
		if (result)
		{
			pugi::xml_node items_node = doc.child("items");

			for (pugi::xml_node item_node : items_node.children("item"))
			{
				ItemInfo info = ItemInfo();
				info.id = item_node.child("id").text().as_int();
				info.name = std::string(item_node.child("name").text().as_string());
				items[info.id] = info;
			}
		}
		else
		{
			return_value = false;
		}

		free(buffer);
		return return_value;
	}
}