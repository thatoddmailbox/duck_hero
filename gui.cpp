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
		font_size = 16;
		_text_texure = nullptr;
		_text_rect = { 0, 0, 0, 0 };
	}

	GUIButton::~GUIButton()
	{
		if (_text_texure != nullptr)
		{
			SDL_DestroyTexture(_text_texure);
		}
	}

	void GUIButton::Update(SDL_Renderer * r)
	{
		if (_text_texure == nullptr)
		{
			SDL_Surface * text_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ GUI_FONT_NAME, font_size }), text.c_str(), { 255, 255, 255, 255 }, w);
			_text_texure = SDL_CreateTextureFromSurface(r, text_surface);

			_text_rect = { 0, 0, 0, 0 };
			SDL_QueryTexture(_text_texure, NULL, NULL, &_text_rect.w, &_text_rect.h);
			_text_rect.x = x + ((w - _text_rect.w) / 2);
			_text_rect.y = y + ((h - _text_rect.h) / 2);

			SDL_FreeSurface(text_surface);
		}
	}

	void GUIButton::Draw(SDL_Renderer * r)
	{
		SDL_Texture * ui_sheet_texture = Spritesheet::ui.GetTexture(r);

		int left_tile_index = 24;
		int tile_w = Spritesheet::ui.tile_w;
		double scale_factor = (double)h / (double)tile_w;
		int scaled_tile_w = tile_w * scale_factor;

		// left tile
		SDL_Rect left_tile_rect = Spritesheet::ui.GetCoordinatesForTile(left_tile_index, 1);
		SDL_Rect left_dst_rect = { x, y, scaled_tile_w, h };
		SDL_RenderCopy(r, ui_sheet_texture, &left_tile_rect, &left_dst_rect);

		// middle tile
		SDL_Rect middle_tile_rect = Spritesheet::ui.GetCoordinatesForTile(left_tile_index + 1, 1);
		SDL_Rect middle_dst_rect = { x + scaled_tile_w, y, w - (scaled_tile_w * 2), h };
		SDL_RenderCopy(r, ui_sheet_texture, &middle_tile_rect, &middle_dst_rect);

		// right tile
		SDL_Rect right_tile_rect = Spritesheet::ui.GetCoordinatesForTile(left_tile_index + 2, 1);
		SDL_Rect right_dst_rect = { x + w - scaled_tile_w, y, scaled_tile_w, h };
		SDL_RenderCopy(r, ui_sheet_texture, &right_tile_rect, &right_dst_rect);

		// text
		SDL_RenderCopy(r, _text_texure, NULL, &_text_rect);
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

	void GUIScreen::Update(SDL_Renderer * r)
	{
		for (std::vector<GUIElement *>::iterator it = elements.begin(); it != elements.end(); ++it)
		{
			(*it.base())->Update(r);
		}
	}

	void GUIScreen::Draw(SDL_Renderer * r)
	{
		for (std::vector<GUIElement *>::iterator it = elements.begin(); it != elements.end(); ++it)
		{
			(*it.base())->Draw(r);
		}
	}
}