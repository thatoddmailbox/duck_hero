#ifndef _GUI_MANAGER_HPP
#define _GUI_MANAGER_HPP

#include <memory>

#include "gui.hpp"
#include "gui_bg.hpp"
#include "gui_credits.hpp"
#include "gui_level.hpp"
#include "gui_logo.hpp"
#include "gui_prompt.hpp"
#include "save_manager.hpp"

namespace duckhero
{
	class GUIManager
	{
	public:
		static GUIScreen * current_screen;
		static std::shared_ptr<GUIPrompt> prompt;

		static GUIScreen menu;
		static GUILevelScreen game;
		static GUIScreen credits;

		static void Init();
		static void Update(SDL_Renderer * r);
		static void Draw(SDL_Renderer * r);
	};
}

#endif