#include "save_manager.hpp"

namespace duckhero
{
	std::string SaveManager::GetPathForSlot(int slot_index)
	{
		char * base_path = SDL_GetPrefPath("Flippers", "Duck Hero");
		std::string base_path_str = std::string(base_path);
		SDL_free(base_path);

		return base_path_str + "save" + std::to_string(slot_index) + ".xml";
	}

	void SaveManager::LoadFromFile(std::string path, Level * l)
	{
		pugi::xml_document save_document;
		save_document.load_file(path.c_str());
		pugi::xml_node save_node = save_document.child("save");

		pugi::xml_node player_node = save_node.child("player");
		l->player.x = player_node.attribute("x").as_int();
		l->player.y = player_node.attribute("y").as_int();
		l->player.health = player_node.attribute("health").as_int();
		l->player.coins = player_node.child("coins").text().as_int();

		l->player.current_quests.clear();
		for (pugi::xml_node quest_node : player_node.child("current_quests"))
		{
			l->player.current_quests.push_back(std::string(quest_node.text().as_string()));
		}

		l->player.completed_quests.clear();
		for (pugi::xml_node quest_node : player_node.child("completed_quests"))
		{
			l->player.completed_quests.push_back(std::string(quest_node.text().as_string()));
		}

		l->player.items.clear();
		for (pugi::xml_node item_node : player_node.child("items"))
		{
			l->player.items.push_back(Item(item_node.attribute("id").as_int()));
		}

		for (pugi::xml_node pickup_node : save_node.child("pickups"))
		{
			// find the corresponding pickup entity
			int pickup_x = pickup_node.attribute("x").as_int();
			int pickup_y = pickup_node.attribute("y").as_int();
			for (std::shared_ptr<Entity>& e : l->entities)
			{
				if (Pickup * p = dynamic_cast<Pickup *>(e.get()))
				{
					if (p->x == pickup_x && p->y == pickup_y)
					{
						p->picked_up = true;
						break;
					}
				}
			}
		}
	}

	void SaveManager::SaveToFile(std::string path, Level * l)
	{
		pugi::xml_document save_document;
		pugi::xml_node save_node = save_document.append_child("save");

		pugi::xml_node player_node = save_node.append_child("player");
		player_node.append_attribute("x").set_value(l->player.x);
		player_node.append_attribute("y").set_value(l->player.y);
		player_node.append_attribute("health").set_value(l->player.health);
		player_node.append_child("coins").text().set(l->player.coins);

		pugi::xml_node current_quests_node = player_node.append_child("current_quests");
		for (std::string quest : l->player.current_quests)
		{
			pugi::xml_node quest_node = current_quests_node.append_child("quest");
			quest_node.text().set(quest.c_str());
		}

		pugi::xml_node completed_quests_node = player_node.append_child("completed_quests");
		for (std::string quest : l->player.completed_quests)
		{
			pugi::xml_node quest_node = completed_quests_node.append_child("quest");
			quest_node.text().set(quest.c_str());
		}

		pugi::xml_node items_node = player_node.append_child("items");
		for (Item item : l->player.items)
		{
			pugi::xml_node item_node = items_node.append_child("item");
			item_node.append_attribute("id").set_value(item.id);
		}

		pugi::xml_node pickups_node = save_node.append_child("pickups");
		for (std::shared_ptr<Entity>& e : l->entities)
		{
			if (Pickup * p = dynamic_cast<Pickup *>(e.get()))
			{
				if (p->picked_up)
				{
					// save that we've picked this up already
					pugi::xml_node pickup_node = pickups_node.append_child("pickup");
					pickup_node.append_attribute("x").set_value(p->x);
					pickup_node.append_attribute("y").set_value(p->y);
				}
			}
		}

		save_document.save_file(path.c_str());
	}
}