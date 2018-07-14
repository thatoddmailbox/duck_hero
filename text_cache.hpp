#ifndef _TEXT_CACHE_HPP
#define _TEXT_CACHE_HPP

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "content.hpp"
#include "lru_cache.hpp"

namespace duckhero
{
	class TextCache
	{
	private:
		LRUCache<std::string, SDL_Texture *> _cache = LRUCache<std::string, SDL_Texture *>(0, nullptr);
		std::string _font_name;
		int _font_size;
		SDL_Color _color;
		int _wrap_width;
	public:
		TextCache(std::string in_font_name, int in_font_size, SDL_Color in_color, int in_wrap_width);
		void Draw(SDL_Renderer * r, std::string text, int x, int y);
	};
}

#endif