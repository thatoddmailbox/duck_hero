#include "gui_logo.hpp"

namespace duckhero
{
	GUILogo::GUILogo()
	{
		_text_texture = nullptr;
		_text_rect = { 0, 0, 0, 0 };
		_logo_rect = { 0, 0, 0, 0 };
	}

	GUILogo::~GUILogo()
	{
		if (_text_texture)
		{
			SDL_DestroyTexture(_text_texture);
		}
	}

	bool GUILogo::Update(SDL_Renderer * r)
	{
		return false;
	}

	void GUILogo::Draw(SDL_Renderer * r)
	{
		if (_text_texture == nullptr)
		{
			SDL_Surface * text_surface = TTF_RenderText_Blended(Content::GetFont({ GUI_FONT_NAME, 48 }), "Duck Hero", { 0, 0, 0, 255 });
			_text_texture = SDL_CreateTextureFromSurface(r, text_surface);

			_text_rect = { 0, 0, 0, 0 };
			SDL_QueryTexture(_text_texture, NULL, NULL, &_text_rect.w, &_text_rect.h);

			int width = _text_rect.w + 200;
			int height = _text_rect.h + 20;
			_logo_rect = { (WINDOW_WIDTH - width) / 2, 50, width, height };

			_text_rect.x = _logo_rect.x + ((_logo_rect.w - _text_rect.w) / 2);
			_text_rect.y = _logo_rect.y + ((_logo_rect.h - _text_rect.h) / 2);

			SDL_FreeSurface(text_surface);
		}

		// draw outline
		GUIHelper::DrawFrame(r, _logo_rect, GUIHelper::FRAME_DARK_BROWN_PAPER);

		SDL_RenderCopy(r, _text_texture, NULL, &_text_rect);
	}

	void GUILogo::HandleAction()
	{

	}
}