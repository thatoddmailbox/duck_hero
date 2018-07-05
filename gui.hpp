#ifndef _GUI_HPP
#define _GUI_HPP

#include <map>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "content.hpp"

namespace duckhero
{
	class GUIElement
	{
	public:
		int x, y, w, h;

		virtual void Draw(SDL_Renderer * r) = 0;
		virtual void HandleAction() = 0;
	};

	class GUIButton : public GUIElement
	{
	public:
		std::string text;

		GUIButton(std::string in_text, int in_x, int in_y, int in_w, int in_h);
		void Draw(SDL_Renderer * r) override;
		void HandleAction() override;
	};

	class GUIScreen
	{
	public:
		void AddElement(GUIElement * e);
		void Draw(SDL_Renderer * r);
	private:
		std::vector<GUIElement *> elements;
	};
}

#endif