#include "gui_work.hpp"

#include "gui_level.hpp"

namespace duckhero
{
	void work_close(GUIButton * button)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) button->metadata;
		level_screen->work = nullptr;
	}

	GUIWork::GUIWork(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;
		state = GUIWorkState::Select;
		nonogram = Nonogram();
		rect = { (WINDOW_WIDTH - 700) / 2, (WINDOW_HEIGHT - 400) / 2, 700, 400 };
		close.metadata = level_screen_pointer;
	}

	void GUIWork::Update(SDL_Renderer * r)
	{
		close.Update(r);
	}

	void GUIWork::Draw(SDL_Renderer * r)
	{
		GUIHelper::DrawMenuOverlay(r);
		GUIHelper::DrawFrame(r, rect, GUIHelper::FRAME_BROWN_PAPER);

		if (state == GUIWorkState::Select)
		{

		}
		else if (state == GUIWorkState::Puzzle)
		{
			SDL_Rect nonogram_rect;
		}
		else if (state == GUIWorkState::MissingPermit)
		{
			_title_cache.Draw(r, "You're missing a Work Permit, which is required before you can use this machine!", rect.x + 10, rect.y + 10);
		}

		close.Draw(r);
	}
}