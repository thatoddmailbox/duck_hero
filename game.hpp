#ifndef _GAME_HPP
#define _GAME_HPP

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "external/physfsrwops.h"

#include "content.hpp"
#include "gui_manager.hpp"
#include "input.hpp"
#include "level.hpp"

namespace duckhero
{
	class Game
	{
	private:
		bool _running;
		SDL_Window * _window;
		SDL_Renderer * _renderer;
	public:
		Game();
		~Game();

		void FatalSDLError(std::string error);
		static void Warning(std::string tag, std::string message);
		int Run();
	};	
}


#endif