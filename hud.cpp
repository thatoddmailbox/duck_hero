#include "hud.hpp"

namespace duckhero
{
	HUD::HUD()
	{
		_screen = GUIScreen();
		_dialogueState = {};
	}

	void HUD::Update(SDL_Renderer * r, Player * player, Level * level)
	{
		_screen.Update(r);
		GUIDialogue::Update(r, level, &_dialogueState);
	}

	void HUD::Draw(SDL_Renderer * r, Player * player, Level * level)
	{
		_screen.Draw(r);
		GUIDialogue::Draw(r, level, &_dialogueState);
	}
}