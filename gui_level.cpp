#include "gui_level.hpp"

namespace duckhero
{
	//
	// GUILevelScreen
	//
	void GUILevelScreen::Update(SDL_Renderer * r)
	{
		GUIScreen::Update(r);
	}

	void GUILevelScreen::Draw(SDL_Renderer * r)
	{
		level.Draw(r, camera_x, camera_y);
		GUIScreen::Draw(r);
	}
}