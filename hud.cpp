#include "hud.hpp"

namespace duckhero
{
	void open_menu(GUIButton * button)
	{
		HUD * hud = (HUD *) button->metadata;

		hud->level->showing_menu = true;
		hud->menu = GUIMenu(hud->level);
	}

	HUD::HUD(std::shared_ptr<Level> in_level)
	{
		_screen = GUIScreen();
		_hud_state = {};
		level = in_level;

		_hud_state.menu_button = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Menu", 1024 - 150, 600 - 32, 150, 32, &open_menu));
		_hud_state.menu_button->metadata = this;
	}

	HUD::HUD(const HUD& other)
	{
		_screen = other._screen;
		_hud_state = other._hud_state;
		if (_hud_state.menu_button)
		{
			_hud_state.menu_button->metadata = this;
		}
		level = other.level;
		menu = other.menu;
	}

	HUD& HUD::operator=(const HUD& other)
	{
		_screen = other._screen;
		_hud_state = other._hud_state;
		if (_hud_state.menu_button)
		{
			_hud_state.menu_button->metadata = this;
		}
		level = other.level;
		menu = other.menu;
		return *this;
	}

	void HUD::Update(SDL_Renderer * r)
	{
		if (level->showing_menu)
		{
			menu.Update(r);
		}

		_screen.Update(r);

		if (!level->dialogueManager.showingLine)
		{
			_hud_state.menu_button->Update(r);
		}

		GUIDialogue::Update(r, level, &_hud_state);
	}

	void HUD::Draw(SDL_Renderer * r)
	{
		if (level->showing_menu)
		{
			menu.Draw(r);
		}

		_screen.Draw(r);

		if (!level->dialogueManager.showingLine)
		{
			_hud_state.menu_button->Draw(r);
		}

		GUIDialogue::Draw(r, level, &_hud_state);
	}
}