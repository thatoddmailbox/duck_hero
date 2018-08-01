#include "gui_manager.hpp"

namespace duckhero
{
	GUIScreen * GUIManager::current_screen = &menu;
	std::shared_ptr<GUIPrompt> GUIManager::prompt = nullptr;

	GUIScreen GUIManager::menu = GUIScreen();
	GUILevelScreen GUIManager::game = GUILevelScreen();

	void menu_dismiss_alert(GUIPrompt * prompt, std::string action)
	{
		GUIManager::prompt = nullptr;
	}

	void menu_new(GUIButton * button)
	{
		GUIManager::game.SetLevel(std::shared_ptr<Level>(new Level()));
		GUIManager::game.GetLevel()->LoadFromFile("levels/duckville.tmx");
		GUIManager::game.GetLevel()->player.x = 4 * 32;
		GUIManager::game.GetLevel()->player.y = 11 * 32;
		GUIManager::current_screen = &GUIManager::game;
	}

	void menu_load(GUIButton * button)
	{
		GUIManager::game.SetLevel(std::shared_ptr<Level>(new Level()));
		GUIManager::game.GetLevel()->LoadFromFile("levels/duckville.tmx");
		if (SaveManager::LoadFromFile(SaveManager::GetPathForSlot(0), GUIManager::game.GetLevel().get()))
		{
			GUIManager::current_screen = &GUIManager::game;
		}
		else
		{
			std::map<std::string, GUIPromptHandler> actions;
			actions["OK"] = &menu_dismiss_alert;
			std::shared_ptr<GUIPrompt> alert_prompt = std::shared_ptr<GUIPrompt>(new GUIPrompt(nullptr, "You don't have a saved game to load!", actions));
			GUIManager::prompt = alert_prompt;
		}
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

		menu.AddElement(std::shared_ptr<GUIElement>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "New game", (WINDOW_WIDTH - 200) / 2, 130, 200, 32, &menu_new)));
		menu.AddElement(std::shared_ptr<GUIElement>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Load game", (WINDOW_WIDTH - 200) / 2, 130 + ((32 + 10) * 1), 200, 32, &menu_load)));
		menu.AddElement(std::shared_ptr<GUIElement>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Quit", (WINDOW_WIDTH - 200) / 2, 130 + ((32 + 10) * 2), 200, 32, &menu_quit)));

		//
		// game
		//
	}

	void GUIManager::Update(SDL_Renderer * r)
	{
		current_screen->Update(r);
		if (prompt)
		{
			prompt->Update(r);
		}
	}

	void GUIManager::Draw(SDL_Renderer * r)
	{
		current_screen->Draw(r);
		if (prompt)
		{
			prompt->Draw(r);
		}
	}
}