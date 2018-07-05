#include "gui.hpp"

namespace duckhero
{
	//
	// GUIButton
	//
	GUIButton::GUIButton(std::string in_text, int in_x, int in_y, int in_w, int in_h)
	{
		text = in_text;
		x = in_x;
		y = in_y;
		w = in_w;
		h = in_h;
	}

	void GUIButton::Draw(SDL_Renderer * r)
	{
		SDL_Surface * textSurf = TTF_RenderText_Blended_Wrapped(Content::GetFont({ "fonts/fixedsys.ttf", 24 }), text.c_str(), { 255, 255, 255, 255 }, 780);
		SDL_Texture * textTex = SDL_CreateTextureFromSurface(r, textSurf);

		SDL_Rect textRect = { x, y, 0, 0 };
		SDL_QueryTexture(textTex, NULL, NULL, &textRect.w, &textRect.h);

		SDL_RenderCopy(r, textTex, NULL, &textRect);

		SDL_DestroyTexture(textTex);
		SDL_FreeSurface(textSurf);

		SDL_RenderPresent(r);
	}

	void GUIButton::HandleAction()
	{
		
	}

	//
	// GUIScreen
	//
	void GUIScreen::AddElement(GUIElement * e)
	{
		elements.push_back(e);
	}

	void GUIScreen::Draw(SDL_Renderer * r)
	{
		for (std::vector<GUIElement *>::iterator it = elements.begin(); it != elements.end(); ++it)
		{
			(*it.base())->Draw(r);
		}
	}
}