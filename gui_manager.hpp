#ifndef _GUI_MANAGER_HPP
#define _GUI_MANAGER_HPP

#include "gui.hpp"
#include "gui_level.hpp"

namespace duckhero
{
	class GUIManager
	{
	public:
		static GUIScreen * current_screen;

		static GUIScreen menu;
		static GUILevelScreen game;

		static void Init();
		static void Update(SDL_Renderer * r);
		static void Draw(SDL_Renderer * r);
	};
}

#endif