#ifndef _GUI_NONOGRAM_HPP
#define _GUI_NONOGRAM_HPP

#include <SDL.h>

#include "consts.hpp"
#include "input.hpp"
#include "nonogram.hpp"

namespace duckhero
{
	class GUINonogram
	{
	public:
		static SDL_Rect GetCenterRectForNonogram(SDL_Rect& container, Nonogram * n);
		static void Update(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect);
		static void Draw(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect);
	};
}

#endif