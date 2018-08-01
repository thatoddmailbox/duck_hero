#ifndef _HUD_HPP
#define _HUD_HPP

#include "consts.hpp"
#include "gui.hpp"
#include "gui_dialogue.hpp"
#include "gui_menu.hpp"
#include "level.hpp"
#include "hud_state.hpp"
#include "text_cache.hpp"
#include "spritesheet.hpp"

namespace duckhero
{
	class HUD
	{
	private:
		GUIScreen _screen;
		TextCache _text_cache = TextCache(GUI_FONT_NAME, 18, { 0, 0, 0, 255 }, GUI_MENU_WIDTH);
	public:
		HUDState hud_state;
		std::shared_ptr<Level> level;
		GUIMenu menu = GUIMenu(nullptr);

		HUD(std::shared_ptr<Level> in_level);
		HUD(const HUD& other);
		HUD& operator=(const HUD& other);

		void Update(SDL_Renderer * r, bool show_menu_button);
		void Draw(SDL_Renderer * r, bool show_menu_button);
	};
}

#endif