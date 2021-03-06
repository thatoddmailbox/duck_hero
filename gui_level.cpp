#include "gui_level.hpp"

namespace duckhero
{
	//
	// GUILevelScreen
	//
	GUILevelScreen::GUILevelScreen()
	{
		_level = std::shared_ptr<Level>(new Level());
		prompt = nullptr;
		shop = nullptr;
		work = nullptr;
		hud = HUD(_level);
		camera_x = camera_y = 0;
	}

	bool GUILevelScreen::IsSomethingOpen()
	{
		return _level->dialogueManager.showingLine || _level->showing_menu || prompt.get() != nullptr || shop.get() != nullptr || work.get() != nullptr;
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
		if (!IsSomethingOpen())
		{
			int speed = 2;

			_level->player.walking = false;

			if (Input::IsButtonDown(Button::UP))
			{
				_level->TryMoveEntity(&_level->player, 0, -speed);
				_level->player.direction = DIRECTION_UP;
				_level->player.walking = true;
			}
			else if (Input::IsButtonDown(Button::DOWN))
			{
				_level->TryMoveEntity(&_level->player, 0, speed);
				_level->player.direction = DIRECTION_DOWN;
				_level->player.walking = true;
			}

			if (Input::IsButtonDown(Button::LEFT))
			{
				_level->TryMoveEntity(&_level->player, -speed, 0);
				_level->player.direction = DIRECTION_LEFT;
				_level->player.walking = true;
			}
			else if (Input::IsButtonDown(Button::RIGHT))
			{
				_level->TryMoveEntity(&_level->player, speed, 0);
				_level->player.direction = DIRECTION_RIGHT;
				_level->player.walking = true;
			}

			if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_F3])
			{
				std::string path = SaveManager::GetPathForSlot(0);
				SaveManager::SaveToFile(path, _level.get());
			}
			else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_F2])
			{
				std::string path = SaveManager::GetPathForSlot(0);
				SaveManager::LoadFromFile(path, _level.get());
			}

			if (Input::IsButtonReleased(Button::INTERACT))
			{
				_level->TryInteract(this);
			}
		}

		camera_x = -(_level->player.x - (WINDOW_WIDTH/2) + 16);
		camera_y = -(_level->player.y - (WINDOW_HEIGHT/2) + 16);

		int max_camera_x = -((_level->width * 32) - WINDOW_WIDTH);
		int max_camera_y = -((_level->height * 32) - WINDOW_HEIGHT);

		if (camera_x > 0)
		{
			camera_x = 0;
		}
		if (camera_x < max_camera_x)
		{
			camera_x = max_camera_x;
		}
		if (camera_y > 0)
		{
			camera_y = 0;
		}
		if (camera_y < max_camera_y)
		{
			camera_y = max_camera_y;
		}

		_level->Update(r);
		hud.Update(r, (shop == nullptr && prompt == nullptr && work == nullptr));
		GUIScreen::Update(r);

		if (work != nullptr && prompt == nullptr)
		{
			work->Update(r, this);
		}
		if (shop != nullptr)
		{
			shop->Update(r);
		}
		if (prompt != nullptr)
		{
			prompt->Update(r);
		}
	}

	void GUILevelScreen::Draw(SDL_Renderer * r)
	{
		_level->Draw(r, camera_x, camera_y);
		if (shop == nullptr && work == nullptr)
		{
			// only draw the hud here if the shop and work gui are both closed
			// that way, when they are open, we draw the hud above them
			// then the user can see the coin count
			hud.Draw(r, (prompt == nullptr));
		}
		GUIScreen::Draw(r);

		if (work != nullptr)
		{
			work->Draw(r);
		}
		if (shop != nullptr)
		{
			shop->Draw(r);
		}
		if (prompt != nullptr)
		{
			prompt->Draw(r);
		}

		if (work != nullptr || shop != nullptr)
		{
			hud.Draw(r, false);
		}
	}
}