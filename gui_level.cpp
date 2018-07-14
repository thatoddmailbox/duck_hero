#include "gui_level.hpp"

namespace duckhero
{
	//
	// GUILevelScreen
	//
	GUILevelScreen::GUILevelScreen()
	{
		_level = std::shared_ptr<Level>(new Level());
		hud = HUD(_level);
	}

	std::shared_ptr<Level> GUILevelScreen::GetLevel()
	{
		return _level;
	}

	void GUILevelScreen::SetLevel(std::shared_ptr<Level> new_level)
	{
		_level = new_level;
		hud.level = _level;
	}

	void GUILevelScreen::Update(SDL_Renderer * r)
	{
		if (!_level->dialogueManager.showingLine && !_level->showing_menu)
		{
			int speed = 2;

			if (Input::IsButtonDown(Button::UP))
			{
				_level->TryMoveEntity(&_level->player, 0, -speed);
			}
			else if (Input::IsButtonDown(Button::DOWN))
			{
				_level->TryMoveEntity(&_level->player, 0, speed);
			}

			if (Input::IsButtonDown(Button::LEFT))
			{
				_level->TryMoveEntity(&_level->player, -speed, 0);
			}
			else if (Input::IsButtonDown(Button::RIGHT))
			{
				_level->TryMoveEntity(&_level->player, speed, 0);
			}

			if (Input::IsButtonReleased(Button::INTERACT))
			{
				_level->TryInteract();
			}
		}

		camera_x = -(_level->player.x - (1024/2) + 16);
		camera_y = -(_level->player.y - (600/2) + 16);

		hud.Update(r);

		GUIScreen::Update(r);
	}

	void GUILevelScreen::Draw(SDL_Renderer * r)
	{
		_level->Draw(r, camera_x, camera_y);
		hud.Draw(r);
		GUIScreen::Draw(r);
	}
}