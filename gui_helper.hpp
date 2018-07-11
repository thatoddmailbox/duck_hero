#ifndef _GUI_HELPER_HPP
#define _GUI_HELPER_HPP

#include <SDL.h>

#include "spritesheet.hpp"

namespace duckhero
{
	class GUIHelper
	{
	public:
		static const int FRAME_BROWN_PAPER = 390;
		static const int FRAME_MODERN = 613;

		static void DrawFrame(SDL_Renderer * r, SDL_Rect location, int top_left_tile);
	};
}

#endif