#ifndef _GUI_PROMPT_HPP
#define _GUI_PROMPT_HPP

#include <map>
#include <string>
#include <vector>

#include <SDL.h>

#include "consts.hpp"
#include "gui.hpp"
#include "gui_helper.hpp"
#include "text_cache.hpp"

#define GUI_PROMPT_CONTENT_WIDTH 200

namespace duckhero
{
	void prompt_close(GUIButton * button);

	class GUIPrompt;

	typedef void (*GUIPromptHandler)(GUIPrompt *, std::string);

	class GUIPrompt
	{
	private:
		std::vector<GUIButton> _buttons;

		TextCache _text_cache = TextCache(GUI_FONT_NAME, 16, { 0, 0, 0, 255 }, GUI_PROMPT_CONTENT_WIDTH);
	public:
		GUIButton close = GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Close", WINDOW_WIDTH - 150, WINDOW_HEIGHT - 32, 150, 32, &prompt_close);
		std::string message;
		std::map<std::string, GUIPromptHandler> actions;
		SDL_Rect window_rect;

		void * metadata;
		void * metadata_2;
		int metadata_3;

		GUIPrompt(void * level_screen_pointer, std::string in_message, std::map<std::string, GUIPromptHandler> in_actions);

		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);
	};
}

#endif