#include "gui_manager.hpp"

namespace duckhero
{
	GUIScreen GUIManager::menu = GUIScreen();

	GUIScreen * GUIManager::current_screen = &menu;

	void GUIManager::Init()
	{
		GUIButton * play = new GUIButton("Test", 10, 10, 100, 40);
		menu.AddElement(play);
	}

	void GUIManager::Draw(SDL_Renderer * r)
	{
		current_screen->Draw(r);
	}
}