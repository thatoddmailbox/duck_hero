#ifndef _GUI_LEVEL_HPP
#define _GUI_LEVEL_HPP

#include <SDL.h>

#include "gui.hpp"
#include "level.hpp"
#include "hud.hpp"

namespace duckhero
{
	class GUILevelScreen : public GUIScreen
	{
	public:
		GUILevelScreen();

		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);

		Level level;
		HUD hud;
		int camera_x, camera_y;
	};
}

#endif