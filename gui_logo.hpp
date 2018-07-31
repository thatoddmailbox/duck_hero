#ifndef _GUI_LOGO_HPP
#define _GUI_LOGO_HPP

#include "gui.hpp"
#include "gui_helper.hpp"

#include <SDL.h>

namespace duckhero
{
	class GUILogo : public GUIElement
	{
	private:
		SDL_Texture * _text_texture;
		SDL_Rect _text_rect;
		SDL_Rect _logo_rect;
	public:
		GUILogo();
		~GUILogo();
		bool Update(SDL_Renderer * r) override;
		void Draw(SDL_Renderer * r) override;
		void HandleAction() override;
	};
}

#endif