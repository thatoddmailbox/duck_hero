#include "gui_manager.hpp"

namespace duckhero
{
	GUIScreen * GUIManager::current_screen = &menu;

	GUIScreen GUIManager::menu = GUIScreen();

	void menutest()
	{
		printf("yay\n");
	}

	void GUIManager::Init()
	{
		GUIButton * play = new GUIButton("Test", 10, 10, 200, 32, &menutest);
		menu.AddElement(play);
	}

	void GUIManager::Update(SDL_Renderer * r)
	{
		current_screen->Update(r);
	}

	void GUIManager::Draw(SDL_Renderer * r)
	{
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderClear(r);
		current_screen->Draw(r);
		SDL_RenderPresent(r);
	}
}