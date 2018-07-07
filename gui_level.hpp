#ifndef _GUI_LEVEL_HPP
#define _GUI_LEVEL_HPP

#include <SDL.h>

#include "gui.hpp"
#include "level.hpp"

namespace duckhero
{
	class GUILevelScreen : public GUIScreen
	{
	public:
		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);

		Level level;
		int camera_x, camera_y;
	};
}

#endif