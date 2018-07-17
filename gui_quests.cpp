#include "gui_quests.hpp"

namespace duckhero
{
	GUIQuests::GUIQuests(std::shared_ptr<Level> in_level, SDL_Rect in_rect)
	{
		GUIScreen::GUIScreen();

		level = in_level;
		_rect = in_rect;

		quest_info = std::map<std::string, Quest>();

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

		int current_y = _rect.y;
		for (std::string& quest_name : level->player.current_quests)
		{
			Quest q = quest_info[quest_name];

			SDL_Rect title_rect = _title_cache.Draw(r, q.display_name, _rect.x, current_y);
			current_y += title_rect.h;

			for (Task& t : q.tasks)
			{
				SDL_Rect task_rect = _desc_cache.Draw(r, t.display, _rect.x + 16, current_y);
				current_y += task_rect.h;
			}

			current_y += 18;
		}

		if (level->player.current_quests.size() == 0)
		{
			_title_cache.Draw(r, "You have no quests!", _rect.x, _rect.y);
		}
	}
}