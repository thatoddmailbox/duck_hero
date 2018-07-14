#ifndef _GUI_ITEMS_HPP
#define _GUI_ITEMS_HPP

#include <map>
#include <memory>
#include <vector>

#include "gui.hpp"
#include "item.hpp"
#include "item_manager.hpp"
#include "level.hpp"
#include "text_cache.hpp"

namespace duckhero
{
	class GUIItems : public GUIScreen
	{
	private:
		TextCache _title_cache = TextCache(GUI_FONT_NAME, 18, { 0, 0, 0, 255 }, GUI_MENU_WIDTH);
		TextCache _desc_cache = TextCache(GUI_FONT_NAME, 16, { 0, 0, 0, 255 }, GUI_MENU_WIDTH);
		SDL_Rect _rect;
	public:
		std::map<std::string, Quest> quest_info;
		std::shared_ptr<Level> level;

		GUIItems(std::shared_ptr<Level> in_level, SDL_Rect in_rect);

		void Update(SDL_Renderer * r) override;
		void Draw(SDL_Renderer * r) override;
	};
}

#endif