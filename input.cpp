#include "input.hpp"

namespace duckhero
{
	MouseState Input::_mouse_state = MouseState();
	SDL_Rect Input::_mouse_rect = { 0, 0, 1, 1 };

	void Input::Update()
	{
		_mouse_state.buttons = SDL_GetMouseState(&_mouse_state.x, &_mouse_state.y);
		_mouse_rect.x = _mouse_state.x;
		_mouse_rect.y = _mouse_state.y;
	}

	MouseState Input::GetMouseState()
	{
		return _mouse_state;
	}

	SDL_Rect Input::GetMouseRect()
	{
		return _mouse_rect;
	}
}