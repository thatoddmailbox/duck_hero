#include "hud.hpp"

namespace duckhero
{
	HUD::HUD()
	{
		_screen = GUIScreen();
	}

	void HUD::Update(SDL_Renderer * r, Player * player)
	{
		_screen.Update(r);
	}

	void HUD::Draw(SDL_Renderer * r, Player * player)
	{
		_screen.Draw(r);
	}
}