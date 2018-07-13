#include "quest.hpp"

#include "level.hpp"

namespace duckhero
{
	bool Quest::LoadXMLInfo(std::string path)
	{
		std::string full_path = "quests/" + path + ".xml";

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
			pugi::xml_node quest = doc.child("quest");

			name = path;
			display_name = std::string(quest.child_value("name"));
			npc = std::string(quest.child_value("npc"));
			dialogue_prompt = std::string(quest.child("dialogue").child_value("prompt"));
			dialogue_accept = std::string(quest.child("dialogue").child_value("accept"));
			dialogue_decline = std::string(quest.child("dialogue").child_value("decline"));

			for (pugi::xml_node requirement_node : quest.child("requirements").children("requirement"))
			{
				Requirement requirement = Requirement();

				requirement.data_string = std::string(requirement_node.child("data").text().as_string());
				requirement.data = requirement_node.child("data").text().as_int();
				const char * type = requirement_node.child("type").text().as_string();

				if (strcmp(type, "coins") == 0)
				{
					requirement.type = RequirementType::CoinsRequirement;
				}
				else if (strcmp(type, "item") == 0)
				{
					requirement.type = RequirementType::ItemRequirement;
				}
				else if (strcmp(type, "quest") == 0)
				{
					requirement.type = RequirementType::QuestRequirement;
				}

				requirements.push_back(requirement);
			}

			for (pugi::xml_node task_node : quest.child("tasks").children("task"))
			{
				Task task = Task();

				task.display = std::string(task_node.child_value("display"));
				task.data = task_node.child("data").text().as_int();
				const char * type = task_node.child("type").text().as_string();

				if (strcmp(type, "coins") == 0)
				{
					task.type = TaskType::CoinsTask;
				}
				else if (strcmp(type, "item") == 0)
				{
					task.type = TaskType::ItemTask;
				}

				tasks.push_back(task);
			}

			for (pugi::xml_node reward_node : quest.child("rewards").children("reward"))
			{
				Reward reward = Reward();

				reward.data = reward_node.child("data").text().as_int();
				const char * type = reward_node.child("type").text().as_string();

				if (strcmp(type, "coins") == 0)
				{
					reward.type = RewardType::CoinsReward;
				}
				else if (strcmp(type, "item") == 0)
				{
					reward.type = RewardType::ItemReward;
				}

				rewards.push_back(reward);
			}
		}
		else
		{
			return_value = false;
		}

		free(buffer);

		return return_value;
	}

	bool Quest::AllRequirementsMet(void * l)
	{
		Level * level = (Level *) l;

		for (Requirement& r : requirements)
		{
			if (r.type == RequirementType::CoinsRequirement)
			{
				if (level->player.coins < r.data)
				{
					// don't have enough coins
					return false;
				}
			}
			else if (r.type == RequirementType::ItemRequirement)
			{
				bool found_item = false;
				for (Item& item : level->player.items)
				{
					if (item.id == r.data)
					{
						found_item = true;
						break;
					}
				}

				if (!found_item)
				{
					// don't have the item!
					return false;
				}
			}
			else if (r.type == RequirementType::QuestRequirement)
			{
				bool found_quest = false;
				for (std::string quest_name : level->player.completed_quests)
				{
					if (quest_name == r.data_string)
					{
						found_quest = true;
						break;
					}
				}

				if (!found_quest)
				{
					// haven't done the requirement yet!
					return false;
				}
			}
		}

		return true;
	}

	bool Quest::AllTasksDone(void * l)
	{
		Level * level = (Level *) l;

		for (Task& task : tasks)
		{
			if (task.type == TaskType::CoinsTask)
			{
				if (level->player.coins < task.data)
				{
					// don't have enough coins
					return false;
				}
			}
			else if (task.type == TaskType::ItemTask)
			{
				bool found_item = false;
				for (Item& item : level->player.items)
				{
					if (item.id == task.data)
					{
						found_item = true;
						break;
					}
				}

				if (!found_item)
				{
					// don't have the item!
					return false;
				}
			}
		}

		return true;
	}

	bool Quest::HasBeenCompleted(void * l)
	{
		Level * level = (Level *) l;
		for (std::string quest_name : level->player.completed_quests)
		{
			if (quest_name == name)
			{
				return true;
			}
		}
		return false;
	}

}