#include "content.hpp"

namespace duckhero
{
	struct FontDescComparer
	{
		bool operator()(const FontDesc & Left, const FontDesc & Right) const
		{
			return Left.path < Right.path || Left.size < Right.size;
		}
	};

	std::map<FontDesc, TTF_Font *, FontDescComparer> _fonts_cache = std::map<FontDesc, TTF_Font *, FontDescComparer>();
	std::map<std::string, SDL_Surface *> _surfaces_cache = std::map<std::string, SDL_Surface *>();

	TTF_Font * Content::GetFont(FontDesc desc)
	{
		if (_fonts_cache.find(desc) != _fonts_cache.end())
		{
			return _fonts_cache[desc];
		}
		TTF_Font * font = TTF_OpenFontRW(PHYSFSRWOPS_openRead(desc.path.c_str()), 1, desc.size);
		_fonts_cache[desc] = font;
		return _fonts_cache[desc];
	}

	SDL_Surface * Content::GetBitmap(std::string file)
	{
		std::map<std::string, SDL_Surface*>::iterator i = _surfaces_cache.find(file);
		if (i == _surfaces_cache.end())
		{
			SDL_Surface* surf = IMG_Load_RW(PHYSFSRWOPS_openRead(file.c_str()), 1);
			if (surf != NULL && ((file.find("_tile.bmp") != file.npos) || file == "images/zap.bmp" || file == "images/zala.bmp" || file == "images/helperbot.bmp" || file == "images/usefulbot.bmp"))
			{
				SDL_SetColorKey(surf, 1, SDL_MapRGB(surf->format, 255, 255, 255));
			}
			i = _surfaces_cache.insert(i, std::make_pair(file, surf));
		}
		return i->second;
	}
}