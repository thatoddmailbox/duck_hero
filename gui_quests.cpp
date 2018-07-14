#include "gui_quests.hpp"

namespace duckhero
{
	GUIQuests::GUIQuests(std::shared_ptr<Level> in_level, SDL_Rect in_rect)
	{
		GUIScreen::GUIScreen();

		level = in_level;
		_rect = in_rect;

		if (!level.get())
		{
			return;
		}

		for (std::string& quest_name : level->player.current_quests)
		{
			Quest q = Quest();
			q.LoadXMLInfo(quest_name);
			quest_info[quest_name] = q;
		}

		for (std::string& quest_name : level->player.completed_quests)
		{
			Quest q = Quest();
			q.LoadXMLInfo(quest_name);
			quest_info[quest_name] = q;
		}
	}

	void GUIQuests::Update(SDL_Renderer * r)
	{
		GUIScreen::Update(r);
	}

	void GUIQuests::Draw(SDL_Renderer * r)
	{
		GUIScreen::Draw(r);

		for (std::string& quest_name : level->player.current_quests)
		{
			Quest q = quest_info[quest_name];
			_title_cache.Draw(r, q.display_name, _rect.x, _rect.y);
		}

		if (level->player.current_quests.size() == 0)
		{
			_title_cache.Draw(r, "go do something", _rect.x, _rect.y);
		}
	}
}