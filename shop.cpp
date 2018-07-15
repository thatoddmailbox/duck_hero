#include "shop.hpp"

namespace duckhero
{
	bool Shop::LoadXMLInfo(std::string path)
	{
		std::string full_path = "shops/" + path + ".xml";

		// read the file into a string
		PHYSFS_File * f = PHYSFS_openRead(full_path.c_str());
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
			pugi::xml_node shop = doc.child("shop");

			name = path;

			for (pugi::xml_node item_node : shop.child("items").children("item"))
			{
				ShopItem item = {
					item_node.child("id").text().as_int(),
					item_node.child("price").text().as_int()
				};
				items.push_back(item);
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