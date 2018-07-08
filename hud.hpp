#ifndef _HUD_HPP
#define _HUD_HPP

#include "gui.hpp"
#include "level.hpp"

namespace duckhero
{
	class HUD
	{
	private:
		GUIScreen _screen;
	public:
		HUD();

		void Update(SDL_Renderer * r, Player * player);
		void Draw(SDL_Renderer * r, Player * player);
	};
}

#endif