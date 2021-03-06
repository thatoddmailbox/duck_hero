#include "hud.hpp"

namespace duckhero
{
	void toggle_menu(GUIButton * button)
	{
		HUD * hud = (HUD *) button->metadata;

		if (hud->level->showing_menu)
		{
			hud->level->showing_menu = false;
			hud->hud_state.menu_button->text = "Menu";
		}
		else
		{
			hud->level->showing_menu = true;
			hud->menu = GUIMenu(hud->level);
			hud->hud_state.menu_button->text = "Close";
		}
	}

	HUD::HUD(std::shared_ptr<Level> in_level)
	{
		_screen = GUIScreen();
		hud_state = {};
		level = in_level;

		hud_state.menu_button = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Menu", WINDOW_WIDTH - 150, WINDOW_HEIGHT - 32, 150, 32, &toggle_menu));
		hud_state.menu_button->metadata = this;
	}

	HUD::HUD(const HUD& other)
	{
		_screen = other._screen;
		hud_state = other.hud_state;
		if (hud_state.menu_button)
		{
			hud_state.menu_button->metadata = this;
		}
		level = other.level;
		menu = other.menu;
	}

	HUD& HUD::operator=(const HUD& other)
	{
		_screen = other._screen;
		hud_state = other.hud_state;
		if (hud_state.menu_button)
		{
			hud_state.menu_button->metadata = this;
		}
		level = other.level;
		menu = other.menu;
		return *this;
	}

	void HUD::Update(SDL_Renderer * r, bool show_menu_button)
	{
		if (level->showing_menu)
		{
			menu.Update(r);
		}

		_screen.Update(r);

		if (!level->dialogueManager.showingLine && show_menu_button)
		{
			hud_state.menu_button->Update(r);
		}

		GUIDialogue::Update(r, level, &hud_state);
	}

	void HUD::Draw(SDL_Renderer * r, bool show_menu_button)
	{
		// coin display
		GUIHelper::DrawFrame(r, { 0, 0, 100, 40 }, GUIHelper::FRAME_BROWN_PAPER);

		SDL_Rect coin_icon_src_rect = Spritesheet::base.GetCoordinatesForTile(45, 11);
		SDL_Rect coin_icon_dst_rect = { 4, 0, 32, 32 };
		SDL_RenderCopy(r, Spritesheet::base.GetTexture(r), &coin_icon_src_rect, &coin_icon_dst_rect);

		std::string coin_str = std::to_string(level->player.coins);
		_text_cache.Draw(r, coin_str, 4 + 32, 10);
		if (level->showing_menu)
		{
			menu.Draw(r);
		}

		_screen.Draw(r);

		if (!level->dialogueManager.showingLine && show_menu_button)
		{
			hud_state.menu_button->Draw(r);
		}

		GUIDialogue::Draw(r, level, &hud_state);
	}
}