#ifndef _QUEST_HPP
#define _QUEST_HPP

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

#include "physfs.h"

#include "external/pugixml.hpp"

namespace duckhero
{
	enum RequirementType
	{
		CoinsRequirement,
		ItemRequirement,
		QuestRequirement
	};

	enum TaskType
	{
		CoinsTask,
		ItemTask
	};

	enum RewardType
	{
		CoinsReward,
		ItemReward
	};

	struct Requirement
	{
		RequirementType type;
		std::string data_string;
		int data;
	};

	struct Task
	{
		std::string display;
		TaskType type;
		int data;
		bool consumed;
	};

	struct Reward
	{
		RewardType type;
		int data;
	};

	class Quest
	{
	public:
		std::string name;
		std::string display_name;
		std::string npc;
		std::string dialogue_prompt;
		std::string dialogue_accept;
		std::string dialogue_decline;
		std::string dialogue_progress;
		std::string dialogue_complete;
		std::string next;

		std::vector<Requirement> requirements;
		std::vector<Task> tasks;
		std::vector<Reward> rewards;

		bool LoadXMLInfo(std::string path);

		bool AllRequirementsMet(void * l);
		bool AllTasksDone(void * l);

		void Complete(void * l);

		bool HasBeenStarted(void * l);
		bool HasBeenCompleted(void * l);
	};
}

#endif