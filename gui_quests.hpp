#ifndef _GUI_QUESTS_HPP
#define _GUI_QUESTS_HPP

#include <map>
#include <memory>
#include <vector>

#include "gui.hpp"
#include "level.hpp"
#include "text_cache.hpp"
#include "quest.hpp"

namespace duckhero
{
	class GUIQuests : public GUIScreen
	{
	private:
		TextCache _title_cache = TextCache(GUI_FONT_NAME, 18, { 0, 0, 0, 255 }, GUI_MENU_WIDTH);
		TextCache _desc_cache = TextCache(GUI_FONT_NAME, 16, { 0, 0, 0, 255 }, GUI_MENU_WIDTH);
		SDL_Rect _rect;
	public:
		std::map<std::string, Quest> quest_info;
		std::shared_ptr<Level> level;

		GUIQuests(std::shared_ptr<Level> in_level, SDL_Rect in_rect);

		void Update(SDL_Renderer * r) override;
		void Draw(SDL_Renderer * r) override;
	};
}

#endif