#ifndef _HUD_HPP
#define _HUD_HPP

#include "gui.hpp"
#include "gui_dialogue.hpp"
#include "level.hpp"

namespace duckhero
{
	class HUD
	{
	private:
		GUIScreen _screen;
		GUIDialogueState _dialogueState;
	public:
		HUD();

		void Update(SDL_Renderer * r, Player * player, Level * level);
		void Draw(SDL_Renderer * r, Player * player, Level * level);
	};
}

#endif