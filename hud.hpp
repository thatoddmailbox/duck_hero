#ifndef _HUD_HPP
#define _HUD_HPP

#include "gui.hpp"
#include "gui_dialogue.hpp"
#include "level.hpp"
#include "hud_state.hpp"

namespace duckhero
{
	class HUD
	{
	private:
		GUIScreen _screen;
		HUDState _hud_state;
	public:
		std::shared_ptr<Level> level;
		GUIMenu menu = GUIMenu(nullptr);

		HUD(std::shared_ptr<Level> in_level);
		HUD(const HUD& other);
		HUD& operator=(const HUD& other);

		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);
	};
}

#endif