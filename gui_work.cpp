#include "gui_work.hpp"

#include "gui_level.hpp"

namespace duckhero
{
	static void work_close_handle_action(GUIPrompt * prompt, std::string action)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) prompt->metadata;
		if (action == "Close anyway")
		{
			level_screen->work = nullptr;
		}
		else if (action == "OK")
		{
			level_screen->work->GenerateNewNonogram();
		}
		level_screen->prompt = nullptr;
	}

	void work_close(GUIButton * button)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) button->metadata;

		std::map<std::string, GUIPromptHandler> actions;
		actions["Close anyway"] = &work_close_handle_action;
		actions["Resume puzzle"] = &work_close_handle_action;
		std::shared_ptr<GUIPrompt> confirm_prompt = std::shared_ptr<GUIPrompt>(new GUIPrompt(level_screen, "You'll lose your progress on this puzzle!", actions));
		confirm_prompt->metadata = button->metadata;

		level_screen->prompt = confirm_prompt;
	}

	GUIWork::GUIWork(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;

		nonogram = Nonogram();
		rect = { (WINDOW_WIDTH - 700) / 2, (WINDOW_HEIGHT - 500) / 2, 700, 500 };
		close.metadata = level_screen_pointer;

		// check if player has the permit
		bool have_permit = false;
		for (Item& i : level_screen->GetLevel()->player.items)
		{
			if (i.id == GUI_WORK_PERMIT_ITEM_ID)
			{
				have_permit = true;
				break;
			}
		}

		if (have_permit)
		{
			GenerateNewNonogram();
			state = GUIWorkState::Puzzle;
		}
		else
		{
			state = GUIWorkState::MissingPermit;
			nonogram_rect = { 0, 0, 0, 0 };
			puzzle_reward = 0;
		}
	}

	void GUIWork::GenerateNewNonogram()
	{
		// dimensions can vary from 4 to 8
		nonogram.width = (rand() % 5) + 4;
		nonogram.height = (rand() % 5) + 4;
		puzzle_reward = ((nonogram.width * nonogram.height) * 10) / 2;

		nonogram.CreateDataArray();

		for (int x = 0; x < nonogram.width; x++)
		{
			for (int y = 0; y < nonogram.height; y++)
			{
				if ((rand() % 2) == 1)
				{
					nonogram.solution[x][y] = NonogramCell::Filled;
				}
			}
		}

		nonogram.GenerateHints();
		
		nonogram_rect = GUINonogram::GetCenterRectForNonogram(rect, &nonogram);
	}

	void GUIWork::Update(SDL_Renderer * r, void * level_screen_pointer)
	{
		if (state == GUIWorkState::Puzzle)
		{
			if (GUINonogram::Update(r, &nonogram, nonogram_rect))
			{
				GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;

				std::map<std::string, GUIPromptHandler> actions;
				actions["OK"] = &work_close_handle_action;
				std::shared_ptr<GUIPrompt> reward_alert = std::shared_ptr<GUIPrompt>(new GUIPrompt(level_screen, "You earned " + std::to_string(puzzle_reward) + " gold!", actions));
				reward_alert->metadata = level_screen_pointer;

				level_screen->prompt = reward_alert;
				level_screen->GetLevel()->player.coins += puzzle_reward;
			}
		}

		close.Update(r);
	}

	void GUIWork::Draw(SDL_Renderer * r)
	{
		GUIHelper::DrawMenuOverlay(r);
		GUIHelper::DrawFrame(r, rect, GUIHelper::FRAME_BROWN_PAPER);

		if (state == GUIWorkState::Puzzle)
		{
			GUINonogram::Draw(r, &nonogram, nonogram_rect);
			_desc_cache.Draw(r, "Reward for completing puzzle: " + std::to_string(puzzle_reward) + " gold", rect.x + 10, rect.y + rect.h - 16 - 10);
		}
		else if (state == GUIWorkState::MissingPermit)
		{
			_title_cache.Draw(r, "You're missing a Work Permit, which is required to use this machine!", rect.x + 10, rect.y + 10);
		}

		close.Draw(r);
	}
}