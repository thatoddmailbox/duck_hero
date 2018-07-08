#include "gui_level.hpp"

namespace duckhero
{
	//
	// GUILevelScreen
	//
	void GUILevelScreen::Update(SDL_Renderer * r)
	{
		if (Input::IsButtonDown(Button::UP))
		{
			level.player.y -= 1;
		}
		else if (Input::IsButtonDown(Button::DOWN))
		{
			level.player.y += 1;
		}

		if (Input::IsButtonDown(Button::LEFT))
		{
			level.player.x -= 1;
		}
		else if (Input::IsButtonDown(Button::RIGHT))
		{
			level.player.x += 1;
		}

		camera_x = -(level.player.x - (1024/2) - 16);
		camera_y = -(level.player.y - (600/2) - 16);

		GUIScreen::Update(r);
	}

	void GUILevelScreen::Draw(SDL_Renderer * r)
	{
		level.Draw(r, camera_x, camera_y);
		GUIScreen::Draw(r);
	}
}