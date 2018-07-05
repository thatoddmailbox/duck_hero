#ifndef _GAME_HPP
#define _GAME_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
		int Run();
	};	
}


#endif