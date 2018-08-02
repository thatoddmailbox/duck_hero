#ifndef _CONTENT_HPP
#define _CONTENT_HPP

#include <map>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "external/physfsrwops.h"

namespace duckhero
{
	struct FontDesc
	{
		std::string path;
		int size;
	};

	class Content
	{
	private:
		bool _running;
		SDL_Window * _window;
		SDL_Renderer * _renderer;
	public:
		// Gets the specified font resource.
		static TTF_Font * GetFont(FontDesc desc);

		// Gets the specified music resource. DO NOT free the Mix_Music.
		static Mix_Music * GetMusic(std::string file);

		// Gets the specified bitmap resource. DO NOT free the SDL_Surface.
		static SDL_Surface * GetBitmap(std::string file);
	};
}

#endif