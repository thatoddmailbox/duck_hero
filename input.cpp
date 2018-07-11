#include "input.hpp"

namespace duckhero
{
	MouseState Input::_mouse_state = MouseState();
	SDL_Rect Input::_mouse_rect = { 0, 0, 1, 1 };

	std::map<Button, bool> Input::_last_frame_status =
	{
		{ Button::UP, false },
		{ Button::DOWN, false },
		{ Button::LEFT, false },
		{ Button::RIGHT, false },
		{ Button::ADVANCE_DIALOGUE, false },
		{ Button::INTERACT, false }
	};

	std::map<Button, SDL_Keycode> keyboard_bindings =
	{
		{ Button::UP, SDL_SCANCODE_W },
		{ Button::DOWN, SDL_SCANCODE_S },
		{ Button::LEFT, SDL_SCANCODE_A },
		{ Button::RIGHT, SDL_SCANCODE_D },
		{ Button::ADVANCE_DIALOGUE, SDL_SCANCODE_SPACE },
		{ Button::INTERACT, SDL_SCANCODE_E }
	};

	void Input::Update()
	{
		_mouse_state.buttons = SDL_GetMouseState(&_mouse_state.x, &_mouse_state.y);
		_mouse_rect.x = _mouse_state.x;
		_mouse_rect.y = _mouse_state.y;

		for (std::map<Button, bool>::iterator it = _last_frame_status.begin(); it != _last_frame_status.end(); ++it)
		{
			_last_frame_status[it->first] = IsButtonDown(it->first);
		}
	}

	MouseState Input::GetMouseState()
	{
		return _mouse_state;
	}

	SDL_Rect Input::GetMouseRect()
	{
		return _mouse_rect;
	}

	const uint8_t * Input::GetKeyboardState()
	{
		return SDL_GetKeyboardState(NULL);
	}

	bool Input::IsButtonDown(Button b)
	{
		SDL_Keycode keycode = keyboard_bindings.at(b);
		if (GetKeyboardState()[keycode])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Input::IsButtonReleased(Button b)
	{
		if (!Input::IsButtonDown(b) && _last_frame_status[b])
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}