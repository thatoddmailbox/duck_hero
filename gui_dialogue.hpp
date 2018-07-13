#ifndef _GUI_DIALOGUE_HPP
#define _GUI_DIALOGUE_HPP

#include <string>

#include <SDL.h>

#include "dialogue.hpp"
#include "gui.hpp"
#include "gui_helper.hpp"
#include "level.hpp"

namespace duckhero
{
	struct GUIDialogueState
	{
		SDL_Texture * cached_instruction_texture;
		SDL_Rect cached_instruction_rect;

		std::string cached_character;
		SDL_Texture * cached_character_texture;
		SDL_Rect cached_character_rect;

		std::string cached_text;
		SDL_Texture * cached_text_texture;
		SDL_Rect cached_text_rect;

		GUIScreen * action_screen;

		GUIButton * action_button_accept;
		GUIButton * action_button_decline;
	};

	class GUIDialogue
	{
	public:
		static const int WIDTH = 1024 - 100;
		static const int HEIGHT = 150;

		static void Update(SDL_Renderer * r, Level * level, GUIDialogueState * state);
		static void Draw(SDL_Renderer * r, Level * level, GUIDialogueState * state);
	};
}

#endif