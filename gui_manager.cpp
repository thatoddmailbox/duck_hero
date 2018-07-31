#include "gui_manager.hpp"

namespace duckhero
{
	GUIScreen * GUIManager::current_screen = &menu;

	GUIScreen GUIManager::menu = GUIScreen();
	GUILevelScreen GUIManager::game = GUILevelScreen();

	void menu_test(GUIButton * button)
	{
		printf("yay\n");
		GUIManager::current_screen = &GUIManager::game;
	}

	void menu_quit(GUIButton * button)
	{
		SDL_Event quit_event;
		quit_event.type = SDL_QUIT;
		SDL_PushEvent(&quit_event);
	}

	void GUIManager::Init()
	{
		//
		// menu
		//
		menu.AddElement(std::shared_ptr<GUIElement>(new GUIBG()));
		menu.AddElement(std::shared_ptr<GUIElement>(new GUILogo()));

		menu.AddElement(std::shared_ptr<GUIElement>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Test", (WINDOW_WIDTH - 200) / 2, 130, 200, 32, &menu_test)));
		menu.AddElement(std::shared_ptr<GUIElement>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Quit", (WINDOW_WIDTH - 200) / 2, 130 + ((32 + 10) * 1), 200, 32, &menu_quit)));

		//
		// game
		//
		game.SetLevel(std::shared_ptr<Level>(new Level()));
		game.GetLevel()->LoadFromFile("levels/duckville.tmx");
		game.GetLevel()->player.x = 4 * 32;
		game.GetLevel()->player.y = 11 * 32;
	}

	void GUIManager::Update(SDL_Renderer * r)
	{
		current_screen->Update(r);
	}

	void GUIManager::Draw(SDL_Renderer * r)
	{
		current_screen->Draw(r);
	}
}