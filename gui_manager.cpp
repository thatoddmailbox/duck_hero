#include "gui_manager.hpp"

namespace duckhero
{
	GUIScreen * GUIManager::current_screen = &menu;

	GUIScreen GUIManager::menu = GUIScreen();
	GUILevelScreen GUIManager::game = GUILevelScreen();

	void menutest(GUIButton * button)
	{
		printf("yay\n");
		GUIManager::current_screen = &GUIManager::game;
	}

	void GUIManager::Init()
	{
		//
		// menu
		//
		GUIButton * play = new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Test", 10, 10, 200, 32, &menutest);
		menu.AddElement(std::shared_ptr<GUIElement>(play));

		//
		// game
		//
		game.SetLevel(std::shared_ptr<Level>(new Level()));
		game.GetLevel()->LoadFromFile("levels/test.tmx");
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