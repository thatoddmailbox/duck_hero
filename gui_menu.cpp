#include "gui_menu.hpp"

#include "gui_manager.hpp"

namespace duckhero
{
	static void menu_confirm_action(GUIPrompt * prompt, std::string action)
	{
		GUIMenu * menu = (GUIMenu *) prompt->metadata;
		menu->prompt = nullptr;
		if (action == "Continue")
		{
			MusicManager::PlayBackground("music/menu");
			GUIManager::current_screen = &GUIManager::menu;
		}
	}

	void open_tab(GUIButton * button)
	{
		GUIMenu * menu = (GUIMenu *) button->metadata;

		if (button->text == "Save game" || button->text == "Game saved")
		{
			SaveManager::SaveToFile(SaveManager::GetPathForSlot(0), menu->level.get());
			button->text = "Game saved";
			return;
		}

		if (button->text == "Back to menu")
		{
			std::map<std::string, GUIPromptHandler> actions;
			actions["Continue"] = &menu_confirm_action;
			actions["Wait, go back!"] = &menu_confirm_action;
			std::shared_ptr<GUIPrompt> confirm_prompt = std::shared_ptr<GUIPrompt>(new GUIPrompt(nullptr, "You'll lose any unsaved progress!", actions));
			confirm_prompt->metadata = menu;
			menu->prompt = confirm_prompt;
			return;
		}
		
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
			(WINDOW_WIDTH - GUI_MENU_WIDTH) / 2,
			(WINDOW_HEIGHT - GUI_MENU_HEIGHT) / 2,
			GUI_MENU_WIDTH,
			GUI_MENU_HEIGHT
		};

		// create top tabs
		int tab_count = 3;
		int button_width = 200;
		int button_space = 50;
		int button_start_x = rect.x + ((rect.w - (tab_count * (button_width + button_space)) + button_space) / 2);
		int button_top_spacing = 2;
		
		tab_quests = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Quests", button_start_x + ((button_width + button_space) * 0), rect.y + button_top_spacing, button_width, 32, &open_tab));
		tab_items = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Items", button_start_x + ((button_width + button_space) * 1), rect.y + button_top_spacing, button_width, 32, &open_tab));
		tab_save = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Save game", button_start_x + ((button_width + button_space) * 2), rect.y + button_top_spacing, button_width, 32, &open_tab));
		main_menu = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Back to menu", 0, WINDOW_HEIGHT - 32, 150, 32, &open_tab));

		tab_quests->metadata = tab_items->metadata = tab_save->metadata = main_menu->metadata = this;

		screen_base.AddElement(tab_quests);
		screen_base.AddElement(tab_items);
		screen_base.AddElement(tab_save);
		screen_base.AddElement(main_menu);

		SDL_Rect screen_rect = rect;
		screen_rect.y += button_top_spacing; screen_rect.h -= button_top_spacing;
		// make space for the tabs
		screen_rect.y += 32; screen_rect.h -= 32;
		// create a 10 pixel margin
		screen_rect.x += 10; screen_rect.w -= 20;
		screen_rect.y += 10; screen_rect.h -= 20;

		// create screens
		screen_quests = GUIQuests(level, screen_rect);
		screen_items = GUIItems(level, screen_rect);

		// set tab
		SwitchTab(GUIMenuTab::Quests);
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
		tab_save = other.tab_save;
		main_menu = other.main_menu;

		tab_quests->metadata = tab_items->metadata = tab_save->metadata = main_menu->metadata = this;
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
		tab_save = other.tab_save;
		main_menu = other.main_menu;

		tab_quests->metadata = tab_items->metadata = tab_save->metadata = main_menu->metadata = this;

		return *this;
	}

	void GUIMenu::SwitchTab(GUIMenuTab new_tab)
	{
		current_tab = new_tab;
		tab_quests->active = false;
		tab_items->active = false;
		if (new_tab == GUIMenuTab::Quests)
		{
			tab_quests->active = true;
		}
		else if (new_tab == GUIMenuTab::Items)
		{
			tab_items->active = true;
		}
	}

	void GUIMenu::Update(SDL_Renderer * r)
	{
		if (prompt != nullptr)
		{
			prompt->Update(r);
			return;
		}

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
		GUIHelper::DrawMenuOverlay(r);
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

		if (prompt != nullptr)
		{
			prompt->Draw(r);
		}
	}
}