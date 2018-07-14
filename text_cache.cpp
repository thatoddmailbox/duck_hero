#include "text_cache.hpp"

namespace duckhero
{
	void free_texture(SDL_Texture ** t)
	{
		SDL_DestroyTexture(*t);
	}

	TextCache::TextCache(std::string in_font_name, int in_font_size, SDL_Color in_color, int in_wrap_width)
	{
		_cache = LRUCache<std::string, SDL_Texture *>(32, &free_texture);

		_font_name = in_font_name;
		_font_size = in_font_size;
		_color = in_color;
		_wrap_width = in_wrap_width;
	}

	SDL_Rect TextCache::Draw(SDL_Renderer * r, std::string text, int x, int y)
	{
		if (!_cache.Exists(text))
		{
			SDL_Surface * text_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ _font_name, _font_size }), text.c_str(), _color, _wrap_width);
			SDL_Texture * text_texture = SDL_CreateTextureFromSurface(r, text_surface);

			SDL_FreeSurface(text_surface);

			_cache.Put(text, text_texture);
		}

		SDL_Texture * texture = _cache.Get(text);

		SDL_Rect text_rect = { x, y, 0, 0 };
		SDL_QueryTexture(texture, NULL, NULL, &text_rect.w, &text_rect.h);

		SDL_RenderCopy(r, texture, NULL, &text_rect);

		return text_rect;
	}
}