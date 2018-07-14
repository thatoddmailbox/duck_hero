#ifndef _GUI_LEVEL_HPP
#define _GUI_LEVEL_HPP

#include <memory>

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

		std::shared_ptr<Level> level;
		HUD hud = HUD(level);
		int camera_x, camera_y;
	};
}

#endif