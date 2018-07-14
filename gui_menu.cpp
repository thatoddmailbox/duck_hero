#include "gui_menu.hpp"

namespace duckhero
{
	void open_tab(GUIButton * button)
	{
		GUIMenu * menu = (GUIMenu *) button->metadata;
		
		GUIMenuTab new_tab;
		if (button->text == "Quests")
		{
			new_tab = GUIMenuTab::Quests;
		}
		else if (button->text == "Items")
		{
			new_tab = GUIMenuTab::Items;
		}

		menu->SwitchTab(new_tab);
	}

	GUIMenu::GUIMenu(std::shared_ptr<Level> in_level)
	{
		level = in_level;
		rect = SDL_Rect{
			(1024 - GUI_MENU_WIDTH) / 2,
			(600 - GUI_MENU_HEIGHT) / 2,
			GUI_MENU_WIDTH,
			GUI_MENU_HEIGHT
		};

		// create top tabs
		int tab_count = 2;
		int button_width = (rect.w / tab_count);
		
		tab_items = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Items", rect.x + (button_width * 0), rect.y, button_width, 32, &open_tab));
		tab_quests = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Quests", rect.x + (button_width * 1), rect.y, button_width, 32, &open_tab));

		tab_items->metadata = tab_quests->metadata = this;

		screen_base.AddElement(tab_items);
		screen_base.AddElement(tab_quests);

		SDL_Rect screen_rect = rect;
		// make space for the tabs
		screen_rect.y += 32; screen_rect.h -= 32;
		// create a 10 pixel margin
		screen_rect.x += 10; screen_rect.w -= 20;
		screen_rect.y += 10; screen_rect.h -= 20;

		// create screens
		screen_quests = GUIQuests(level, screen_rect);
	}

	GUIMenu::GUIMenu(const GUIMenu& other)
	{
		rect = other.rect;
		screen_base = other.screen_base;
		screen_quests = other.screen_quests;
		screen_items = other.screen_items;
		current_tab = other.current_tab;
		level = other.level;
		tab_items = other.tab_items;
		tab_quests = other.tab_quests;

		tab_items->metadata = tab_quests->metadata = this;
	}

	GUIMenu& GUIMenu::operator=(const GUIMenu& other)
	{
		rect = other.rect;
		screen_base = other.screen_base;
		screen_quests = other.screen_quests;
		screen_items = other.screen_items;
		current_tab = other.current_tab;
		level = other.level;
		tab_items = other.tab_items;
		tab_quests = other.tab_quests;

		tab_items->metadata = tab_quests->metadata = this;

		return *this;
	}

	void GUIMenu::SwitchTab(GUIMenuTab new_tab)
	{
		current_tab = new_tab;
	}

	void GUIMenu::Update(SDL_Renderer * r)
	{
		screen_base.Update(r);

		if (current_tab == GUIMenuTab::Quests)
		{
			screen_quests.Update(r);
		}
		else if (current_tab == GUIMenuTab::Items)
		{
			screen_items.Update(r);
		}
	}

	void GUIMenu::Draw(SDL_Renderer * r)
	{
		GUIHelper::DrawFrame(r, rect, GUIHelper::FRAME_BROWN_PAPER);
		screen_base.Draw(r);

		if (current_tab == GUIMenuTab::Quests)
		{
			screen_quests.Draw(r);
		}
		else if (current_tab == GUIMenuTab::Items)
		{
			screen_items.Draw(r);
		}
	}
}