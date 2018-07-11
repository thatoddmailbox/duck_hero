#ifndef _INPUT_HPP
#define _INPUT_HPP

#include <map>
#include <string>

#include <SDL.h>

namespace duckhero
{
	enum class Button
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ADVANCE_DIALOGUE
	};

	struct MouseState
	{
		int x, y;
		uint32_t buttons;
	};

	class Input
	{
	private:
		static MouseState _mouse_state;
		static SDL_Rect _mouse_rect;
		static std::map<Button, bool> _last_frame_status;
	public:
		static void Update();

		static MouseState GetMouseState();
		static SDL_Rect GetMouseRect();

		static const uint8_t * GetKeyboardState();

		static bool IsButtonDown(Button b);
		static bool IsButtonReleased(Button b);
	};
}

#endif