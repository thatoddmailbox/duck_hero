#ifndef _GUI_LEVEL_HPP
#define _GUI_LEVEL_HPP

#include <memory>

#include <SDL.h>

#include "consts.hpp"
#include "gui.hpp"
#include "gui_prompt.hpp"
#include "gui_shop.hpp"
#include "gui_work.hpp"
#include "level.hpp"
#include "hud.hpp"
#include "save_manager.hpp"

namespace duckhero
{
	class GUILevelScreen : public GUIScreen
	{
	private:
		std::shared_ptr<Level> _level;
	public:
		std::shared_ptr<GUIPrompt> prompt;
		std::shared_ptr<GUIShop> shop;
		std::shared_ptr<GUIWork> work;

		HUD hud = HUD(_level);
		int camera_x, camera_y;

		GUILevelScreen();

		bool IsSomethingOpen();

		std::shared_ptr<Level> GetLevel();
		void SetLevel(std::shared_ptr<Level> new_level);

		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);
	};
}

#endif