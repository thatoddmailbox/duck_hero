#include "hud.hpp"

namespace duckhero
{
	HUD::HUD()
	{
		_screen = GUIScreen();
		_dialogueState = {};
	}

	void HUD::Update(SDL_Renderer * r, Player * player, DialogueManager * dialogueManager)
	{
		_screen.Update(r);
		GUIDialogue::Update(r, dialogueManager, &_dialogueState);
	}

	void HUD::Draw(SDL_Renderer * r, Player * player, DialogueManager * dialogueManager)
	{
		_screen.Draw(r);
		GUIDialogue::Draw(r, dialogueManager, &_dialogueState);
	}
}