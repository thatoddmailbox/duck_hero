#ifndef _GUI_DIALOGUE_HPP
#define _GUI_DIALOGUE_HPP

#include <string>

#include <SDL.h>

#include "dialogue.hpp"
#include "gui.hpp"
#include "gui_helper.hpp"
#include "level.hpp"
#include "hud.hpp"
#include "hud_state.hpp"

namespace duckhero
{
	class GUIDialogue
	{
	public:
		static const int WIDTH = 1024 - 100;
		static const int HEIGHT = 150;

		static void Update(SDL_Renderer * r, std::shared_ptr<Level> level, HUDState * state);
		static void Draw(SDL_Renderer * r, std::shared_ptr<Level> level, HUDState * state);
	};
}

#endif