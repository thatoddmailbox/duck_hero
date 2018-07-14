#include "gui_level.hpp"

namespace duckhero
{
	//
	// GUILevelScreen
	//
	GUILevelScreen::GUILevelScreen()
	{
		level = std::shared_ptr<Level>(new Level());
		hud = HUD(level);
	}

	void GUILevelScreen::Update(SDL_Renderer * r)
	{
		if (!level->dialogueManager.showingLine)
		{
			int speed = 2;

			if (Input::IsButtonDown(Button::UP))
			{
				level->TryMoveEntity(&level->player, 0, -speed);
			}
			else if (Input::IsButtonDown(Button::DOWN))
			{
				level->TryMoveEntity(&level->player, 0, speed);
			}

			if (Input::IsButtonDown(Button::LEFT))
			{
				level->TryMoveEntity(&level->player, -speed, 0);
			}
			else if (Input::IsButtonDown(Button::RIGHT))
			{
				level->TryMoveEntity(&level->player, speed, 0);
			}

			if (Input::IsButtonReleased(Button::INTERACT))
			{
				level->TryInteract();
			}
		}

		camera_x = -(level->player.x - (1024/2) + 16);
		camera_y = -(level->player.y - (600/2) + 16);

		hud.Update(r);

		GUIScreen::Update(r);
	}

	void GUILevelScreen::Draw(SDL_Renderer * r)
	{
		level->Draw(r, camera_x, camera_y);
		hud.Draw(r);
		GUIScreen::Draw(r);
	}
}