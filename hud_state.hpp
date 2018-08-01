#ifndef _HUD_STATE_HPP
#define _HUD_STATE_HPP

#include <memory>
#include <string>

#include <SDL.h>

#include "gui.hpp"

namespace duckhero
{
	struct HUDState
	{
		// dialogue
		SDL_Texture * cached_instruction_texture;
		SDL_Rect cached_instruction_rect;

		std::string cached_character;
		SDL_Texture * cached_character_texture;
		SDL_Rect cached_character_rect;

		std::string cached_text;
		SDL_Texture * cached_text_texture;
		SDL_Rect cached_text_rect;

		GUIScreen * action_screen;

		std::shared_ptr<GUIButton> action_button_accept;
		std::shared_ptr<GUIButton> action_button_decline;

		// hud
		std::shared_ptr<GUIButton>menu_button;
	};
}

#endif