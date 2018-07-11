#include "gui_dialogue.hpp"

namespace duckhero
{
	void GUIDialogue::Update(SDL_Renderer * r, DialogueManager * dialogueManager, GUIDialogueState * state)
	{
		if (state->cached_instruction_texture == nullptr)
		{
			SDL_Surface * instruction_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ GUI_FONT_NAME, 16 }), "Press SPACE to continue...", { 0, 0, 0, 255 }, WIDTH);
			state->cached_instruction_texture = SDL_CreateTextureFromSurface(r, instruction_surface);

			state->cached_instruction_rect = { 0, 0, 0, 0 };
			SDL_QueryTexture(state->cached_instruction_texture, NULL, NULL, &(state->cached_instruction_rect.w), &(state->cached_instruction_rect.h));

			SDL_FreeSurface(instruction_surface);
		}

		if (dialogueManager->showingLine)
		{
			if (state->cached_text_texture == nullptr || dialogueManager->currentLine.text != state->cached_text)
			{
				if (state->cached_text_texture != nullptr)
				{
					SDL_DestroyTexture(state->cached_text_texture);
				}

				std::string text = dialogueManager->currentLine.text;

				SDL_Surface * text_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ GUI_FONT_NAME, 18 }), text.c_str(), { 0, 0, 0, 255 }, WIDTH);
				state->cached_text_texture = SDL_CreateTextureFromSurface(r, text_surface);

				state->cached_text_rect = { 0, 0, 0, 0 };
				SDL_QueryTexture(state->cached_text_texture, NULL, NULL, &(state->cached_text_rect.w), &(state->cached_text_rect.h));

				SDL_FreeSurface(text_surface);

				state->cached_text = text;
			}

			if (Input::IsButtonReleased(Button::ADVANCE_DIALOGUE))
			{
				printf("asdf\n");
				if (dialogueManager->lines.size() > 1)
				{
					// go to the next line
					dialogueManager->lines.erase(dialogueManager->lines.begin());
					dialogueManager->currentLine = dialogueManager->lines.at(0);
				}
				else
				{
					// out of lines!
					dialogueManager->lines.clear();
					dialogueManager->showingLine = false;
				}
			}
		}
	}

	void GUIDialogue::Draw(SDL_Renderer * r, DialogueManager * dialogueManager, GUIDialogueState * state)
	{
		if (dialogueManager->showingLine)
		{
			SDL_Rect frame_rect = { 50, 600 - HEIGHT - 50, WIDTH, HEIGHT };
			GUIHelper::DrawFrame(r, frame_rect, GUIHelper::FRAME_BROWN_PAPER);
			if (state->cached_text_texture != nullptr)
			{
				state->cached_text_rect.x = frame_rect.x + 10;
				state->cached_text_rect.y = frame_rect.y + 10;
				SDL_RenderCopy(r, state->cached_text_texture, NULL, &state->cached_text_rect);
			}
			if (state->cached_instruction_texture != nullptr)
			{
				state->cached_instruction_rect.x = frame_rect.x + 10;
				state->cached_instruction_rect.y = frame_rect.y + (frame_rect.h - state->cached_instruction_rect.h - 10);
				SDL_RenderCopy(r, state->cached_instruction_texture, NULL, &state->cached_instruction_rect);
			}
		}
	}
}