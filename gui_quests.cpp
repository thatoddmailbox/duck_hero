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

		for (std::string quest_name : level->player.current_quests)
		{
			Quest q = Quest();
			q.LoadXMLInfo(quest_name);
			quest_info[quest_name] = q;
		}

		for (std::string quest_name : level->player.completed_quests)
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

		_title_cache.Draw(r, "This is a test", _rect.x, _rect.y);
	}
}