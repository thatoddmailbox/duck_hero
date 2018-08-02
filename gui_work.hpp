#ifndef _GUI_WORK_HPP
#define _GUI_WORK_HPP

#include <SDL.h>

#include "consts.hpp"
#include "gui.hpp"
#include "gui_helper.hpp"
#include "gui_nonogram.hpp"
#include "music_manager.hpp"
#include "nonogram.hpp"
#include "text_cache.hpp"

namespace duckhero
{
	void work_close(GUIButton * button);

	enum GUIWorkState
	{
		Puzzle,
		MissingPermit
	};

	class GUIWork
	{
	private:
		TextCache _title_cache = TextCache(GUI_FONT_NAME, 18, { 0, 0, 0, 255 }, GUI_MENU_WIDTH);
		TextCache _desc_cache = TextCache(GUI_FONT_NAME, 16, { 0, 0, 0, 255 }, GUI_MENU_WIDTH);
	public:
		GUIButton close = GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Close", WINDOW_WIDTH - 150, WINDOW_HEIGHT - 32, 150, 32, &work_close);

		GUIWorkState state;
		Nonogram nonogram;
		SDL_Rect nonogram_rect;
		SDL_Rect rect;

		int puzzle_reward;

		GUIWork(void * level_screen_pointer);

		void GenerateNewNonogram();

		void Update(SDL_Renderer * r, void * level_screen_pointer);
		void Draw(SDL_Renderer * r);
	};
}

#endif