#ifndef _GUI_NONOGRAM_HPP
#define _GUI_NONOGRAM_HPP

#include <SDL.h>

#include "consts.hpp"
#include "input.hpp"
#include "nonogram.hpp"
#include "text_cache.hpp"

namespace duckhero
{
	class GUINonogram
	{
	private:
		static TextCache _hint_cache;
	public:
		static SDL_Rect GetCenterRectForNonogram(SDL_Rect& container, Nonogram * n);
		static bool Update(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect);
		static void Draw(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect);
	};
}

#endif