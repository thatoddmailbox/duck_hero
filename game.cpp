#include "game.hpp"

#include <iostream>

namespace duckhero
{
	Game::Game()
	{
		_running = true;
	}
	
	Game::~Game()
	{

	}

	int Game::Run()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		_window = SDL_CreateWindow("Duck Hero", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
		if (_window == nullptr)
		{
			std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return 1;
		}

		_renderer = SDL_CreateRenderer(_window, 0, 0);
		if (_renderer == nullptr)
		{
			std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return 1;
		}

		SDL_Event e;
		while (_running)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					return 0;
				}
			}
		}

		SDL_DestroyWindow(_window);

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		return 0;
	}
}