#ifndef _GUI_CREDITS_HPP
#define _GUI_CREDITS_HPP

#include "gui.hpp"
#include "text_cache.hpp"

#include <SDL.h>

namespace duckhero
{
	class GUICredits : public GUIElement
	{
	private:
		TextCache _text_cache = TextCache(GUI_FONT_NAME, 24, { 255, 255, 255, 255 }, WINDOW_WIDTH);
	public:
		bool Update(SDL_Renderer * r) override;
		void Draw(SDL_Renderer * r) override;
		void HandleAction() override;
	};
}

#endif