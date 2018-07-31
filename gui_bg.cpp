#include "gui_bg.hpp"

namespace duckhero
{
	GUIBG::GUIBG()
	{
		_bg_texture = nullptr;
		_bg_rect = { 0, 0, 0, 0 };
		_bg_x = 0;
	}

	GUIBG::~GUIBG()
	{
		if (_bg_texture)
		{
			SDL_DestroyTexture(_bg_texture);
		}
	}

	bool GUIBG::Update(SDL_Renderer * r)
	{
		if (_bg_rect.w > 0)
		{
			_bg_x++;
			if (_bg_x > _bg_rect.w)
			{
				_bg_x = 0;
			}
		}

		return false;
	}

	void GUIBG::Draw(SDL_Renderer * r)
	{
		if (_bg_rect.w == 0)
		{
			_bg_texture = SDL_CreateTextureFromSurface(r, Content::GetBitmap("ui/menubg.png"));
			_bg_rect = { 0, 0, 0, 0 };
			SDL_QueryTexture(_bg_texture, NULL, NULL, &_bg_rect.w, &_bg_rect.h);
		}

		_bg_rect.x = -_bg_x;
		SDL_RenderCopy(r, _bg_texture, NULL, &_bg_rect);

		if (_bg_rect.x < -(_bg_rect.w - WINDOW_WIDTH))
		{
			_bg_rect.x = _bg_rect.w - _bg_x;
			SDL_RenderCopy(r, _bg_texture, NULL, &_bg_rect);
		}
	}

	void GUIBG::HandleAction()
	{

	}
}