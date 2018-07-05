#ifndef _GUI_HPP
#define _GUI_HPP

#include <map>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "content.hpp"
#include "spritesheet.hpp"

#define GUI_FONT_NAME "fonts/fixedsys.ttf"

namespace duckhero
{
	class GUIElement
	{
	public:
		int x, y, w, h;

		virtual void Update(SDL_Renderer * r) = 0;
		virtual void Draw(SDL_Renderer * r) = 0;
		virtual void HandleAction() = 0;
	};

	class GUIButton : public GUIElement
	{
	private:
		SDL_Texture * _text_texure;
		SDL_Rect _text_rect;
	public:
		std::string text;
		int font_size;

		GUIButton(std::string in_text, int in_x, int in_y, int in_w, int in_h);
		~GUIButton();
		void Update(SDL_Renderer * r) override;
		void Draw(SDL_Renderer * r) override;
		void HandleAction() override;
	};

	class GUIScreen
	{
	public:
		void AddElement(GUIElement * e);
		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);
	private:
		std::vector<GUIElement *> elements;
	};
}

#endif