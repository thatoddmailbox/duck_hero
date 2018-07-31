#ifndef _GUI_MENUBG_HPP
#define _GUI_MENUBG_HPP

#include "gui.hpp"

#include <SDL.h>

namespace duckhero
{
	class GUIBG : public GUIElement
	{
	private:
		SDL_Texture * _bg_texture;
		SDL_Rect _bg_rect;
		int _bg_x;
	public:
		GUIBG();
		~GUIBG();
		bool Update(SDL_Renderer * r) override;
		void Draw(SDL_Renderer * r) override;
		void HandleAction() override;
	};
}

#endif