#ifndef _GUI_MENU_HPP
#define _GUI_MENU_HPP

#include <memory>

#include <SDL.h>

#include "consts.hpp"
#include "gui.hpp"
#include "gui_helper.hpp"
#include "gui_items.hpp"
#include "gui_prompt.hpp"
#include "gui_quests.hpp"
#include "level.hpp"
#include "save_manager.hpp"

namespace duckhero
{
	enum GUIMenuTab
	{
		Quests,
		Items
	};

	class GUIMenu
	{
	public:
		SDL_Rect rect;

		GUIScreen screen_base;
		GUIQuests screen_quests = GUIQuests(std::shared_ptr<Level>(), { 0, 0, 0, 0});
		GUIItems screen_items = GUIItems(std::shared_ptr<Level>(), { 0, 0, 0, 0});

		GUIMenuTab current_tab = GUIMenuTab::Quests;

		std::shared_ptr<Level> level;

		std::shared_ptr<GUIButton> tab_quests;
		std::shared_ptr<GUIButton> tab_items;
		std::shared_ptr<GUIButton> tab_save;

		std::shared_ptr<GUIButton> main_menu;

		std::shared_ptr<GUIPrompt> prompt;

		GUIMenu(std::shared_ptr<Level> in_level);
		GUIMenu(const GUIMenu& other);
		GUIMenu& operator=(const GUIMenu& other);

		void SwitchTab(GUIMenuTab new_tab);

		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);
	};
}

#endif