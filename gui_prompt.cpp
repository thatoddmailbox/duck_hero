#include "gui_prompt.hpp"

namespace duckhero
{
	static void prompt_handle_action(GUIButton * button)
	{
		GUIPrompt * prompt = (GUIPrompt *) button->metadata;
		prompt->actions[button->text](prompt, button->text);
	}

	GUIPrompt::GUIPrompt(std::string in_message, std::map<std::string, GUIPromptHandler> in_actions)
	{
		message = in_message;
		actions = in_actions;

		int window_margin = 10;
		int text_spacing = 16;
		int button_x = 10;
		int button_height = 32;
		int button_margin = 10;

		int total_width = button_x + GUI_PROMPT_CONTENT_WIDTH + button_x;
		int total_height = window_margin + text_spacing + window_margin + ((button_height + button_margin) * actions.size());

		window_rect = SDL_Rect{
			(WINDOW_WIDTH - total_width) / 2,
			(WINDOW_HEIGHT - total_height) / 2,
			total_width,
			total_height
		};

		int button_y = window_margin + text_spacing + window_margin;
		for (std::map<std::string, GUIPromptHandler>::iterator it = actions.begin(); it != actions.end(); ++it)
		{
			GUIButton button = GUIButton(GUIButtonStyle::OldDarkBrownStyle, it->first, window_rect.x + button_x, window_rect.y + button_y, GUI_PROMPT_CONTENT_WIDTH, button_height, &prompt_handle_action);
			button.metadata = this;
			_buttons.push_back(button);
			button_y += button_height + button_margin;
		}
	}

	void GUIPrompt::Update(SDL_Renderer * r)
	{
		for (GUIButton& button : _buttons)
		{
			button.Update(r);
		}
	}

	void GUIPrompt::Draw(SDL_Renderer * r)
	{
		GUIHelper::DrawMenuOverlay(r);
		GUIHelper::DrawFrame(r, window_rect, GUIHelper::FRAME_BROWN_PAPER);
		_text_cache.Draw(r, message, window_rect.x + 10, window_rect.y + 10);

		for (GUIButton& button : _buttons)
		{
			button.Draw(r);
		}
	}
}