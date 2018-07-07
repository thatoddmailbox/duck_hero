#include "game.hpp"

namespace duckhero
{
	Game::Game()
	{
		_running = true;
	}
	
	Game::~Game()
	{

	}

	void Game::FatalSDLError(std::string error)
	{
		std::cerr << error << " Error: " << SDL_GetError() << std::endl;
		_running = false;
	}

	void Game::Warning(std::string tag, std::string message)
	{
		std::cerr << "[" << tag << "][warning] " << message << std::endl;
	}

	int Game::Run()
	{
		// set up library subsystems
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			FatalSDLError("SDL_Init");
			return 1;
		}

		if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF) == 0)
		{
			FatalSDLError("IMG_Init");
			return 1;
		}

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
		{
			FatalSDLError("Mix_OpenAudio");
			return 1;
		}

		if (TTF_Init() != 0)
		{
			FatalSDLError("TTF_Init");
			return 1;
		}

		if (PHYSFS_init(NULL) == 0)
		{
			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
			std::cerr << "PHYSFS_init Error: " << PHYSFS_getLastError() << std::endl;
			#pragma GCC diagnostic pop
			return 1;
		}

		// set up physicsfs
		// TODO: improve this
		if (PHYSFS_mount("../data", NULL, 1) == 0)
		{
			#pragma GCC diagnostic push
			#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
			std::cerr << "PHYSFS_mount Error: " << PHYSFS_getLastError() << std::endl;
			#pragma GCC diagnostic pop
			return 1;
		}

		// set up game subsystems
		GUIManager::Init();

		// create window
		_window = SDL_CreateWindow("Duck Hero", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 600, SDL_WINDOW_SHOWN);
		if (_window == nullptr)
		{
			FatalSDLError("SDL_CreateWindow");
			return 1;
		}

		_renderer = SDL_CreateRenderer(_window, 0, 0);
		if (_renderer == nullptr)
		{
			FatalSDLError("SDL_CreateRenderer");
			return 1;
		}

		Level l = Level();
		l.LoadFromFile("levels/test.tmx");

		int x = -1400;
		int y = -800;
		uint8_t timer = 0;

		SDL_Event e;
		while (_running)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
				{
					_running = false;
				}
			}

			Input::Update();
			GUIManager::Update(_renderer);

			SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			SDL_RenderClear(_renderer);

			timer++;
			if (timer == 5)
			{
				// x--;
				// y--;
				timer = 0;
			}

			l.Draw(_renderer, x, y);
			GUIManager::Draw(_renderer);

			SDL_RenderPresent(_renderer);
		}

		SDL_DestroyWindow(_window);

		PHYSFS_deinit();
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();

		return 0;
	}
}