#include "gui.hpp"

namespace duckhero
{
	//
	// GUIButton
	//
	GUIButton::GUIButton(GUIButtonStyle in_style, std::string in_text, int in_x, int in_y, int in_w, int in_h, void (*in_handler)(GUIButton *))
	{
		style = in_style;
		text = in_text;
		x = in_x;
		y = in_y;
		w = in_w;
		h = in_h;
		handler = in_handler;
		font_size = 16;
		_text_texture = nullptr;
		_text_hover_texture = nullptr;
		_text_rect = { 0, 0, 0, 0 };
		_rect = { x, y, w, h };
	}

	GUIButton::~GUIButton()
	{
		if (_text_texture != nullptr)
		{
			SDL_DestroyTexture(_text_texture);
		}
		if (_text_hover_texture != nullptr)
		{
			SDL_DestroyTexture(_text_hover_texture);
		}
	}

	void GUIButton::Update(SDL_Renderer * r)
	{
		// handle text texture
		if (_text_texture == nullptr || _saved_text != text)
		{
			SDL_Surface * text_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ GUI_FONT_NAME, font_size }), text.c_str(), { 255, 255, 255, 255 }, w);
			SDL_Surface * text_hover_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ GUI_FONT_NAME, font_size }), text.c_str(), { 255, 255, 0, 255 }, w);
			_text_texture = SDL_CreateTextureFromSurface(r, text_surface);
			_text_hover_texture = SDL_CreateTextureFromSurface(r, text_hover_surface);

			_text_rect = { 0, 0, 0, 0 };
			SDL_QueryTexture(_text_texture, NULL, NULL, &_text_rect.w, &_text_rect.h);
			_text_rect.x = x + ((w - _text_rect.w) / 2);
			_text_rect.y = y + ((h - _text_rect.h) / 2);

			SDL_FreeSurface(text_hover_surface);
			SDL_FreeSurface(text_surface);

			_saved_text = text;
		}

		// check if mouse over
		MouseState mouse_state = Input::GetMouseState();
		SDL_Rect mouse_rect = Input::GetMouseRect();
		if (SDL_HasIntersection(&_rect, &mouse_rect))
		{
			_hover = true;
		}
		else
		{
			_hover = false;
		}

		if (_hover && (mouse_state.buttons & SDL_BUTTON(SDL_BUTTON_LEFT)))
		{
			_clicked = true;
		}
		else
		{
			if (_clicked)
			{
				// we were clicked before, but now aren't
				if (_hover)
				{
					// we're still being hovered over, this means the mouse was clicked and released over this button
					// trigger an action
					HandleAction();
				}
			}
			_clicked = false;
		}
	}

	void GUIButton::Draw(SDL_Renderer * r)
	{
		SDL_Texture * ui_sheet_texture = Spritesheet::ui.GetTexture(r);

		int left_tile_index = (int) style;
		int tile_w = Spritesheet::ui.tile_w;
		double scale_factor = (double)h / (double)tile_w;
		int scaled_tile_w = tile_w * scale_factor;

		if (_clicked)
		{
			left_tile_index += Spritesheet::ui.cols;
		}

		// left tile
		SDL_Rect left_tile_rect = Spritesheet::ui.GetCoordinatesForTile(left_tile_index);
		SDL_Rect left_dst_rect = { x, y, scaled_tile_w, h };
		SDL_RenderCopy(r, ui_sheet_texture, &left_tile_rect, &left_dst_rect);

		// middle tile
		SDL_Rect middle_tile_rect = Spritesheet::ui.GetCoordinatesForTile(left_tile_index + 1);
		SDL_Rect middle_dst_rect = { x + scaled_tile_w, y, w - (scaled_tile_w * 2), h };
		SDL_RenderCopy(r, ui_sheet_texture, &middle_tile_rect, &middle_dst_rect);

		// right tile
		SDL_Rect right_tile_rect = Spritesheet::ui.GetCoordinatesForTile(left_tile_index + 2);
		SDL_Rect right_dst_rect = { x + w - scaled_tile_w, y, scaled_tile_w, h };
		SDL_RenderCopy(r, ui_sheet_texture, &right_tile_rect, &right_dst_rect);

		// text
		SDL_RenderCopy(r, (_hover ? _text_hover_texture : _text_texture), NULL, &_text_rect);
	}

	void GUIButton::HandleAction()
	{
		if (handler)
		{
			handler(this);
		}
	}

	//
	// GUIScreen
	//
	void GUIScreen::AddElement(std::shared_ptr<GUIElement> e)
	{
		elements.push_back(e);
	}

	void GUIScreen::Update(SDL_Renderer * r)
	{
		for (std::vector<std::shared_ptr<GUIElement>>::iterator it = elements.begin(); it != elements.end(); ++it)
		{
			if (!(*it.base())->enabled)
			{
				continue;
			}
			(*it.base())->Update(r);
		}
	}

	void GUIScreen::Draw(SDL_Renderer * r)
	{
		for (std::vector<std::shared_ptr<GUIElement>>::iterator it = elements.begin(); it != elements.end(); ++it)
		{
			if (!(*it.base())->enabled)
			{
				continue;
			}
			(*it.base())->Draw(r);
		}
	}
}