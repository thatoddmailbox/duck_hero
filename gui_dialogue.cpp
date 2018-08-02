#include "gui_dialogue.hpp"

#include "gui_manager.hpp"

namespace duckhero
{
	void accept_quest(GUIButton * button)
	{
		Level * level = (Level *) button->metadata;

		std::string quest_name = level->dialogueManager.currentLine.metadata;
		Quest quest = Quest();
		quest.LoadXMLInfo(quest_name);

		level->dialogueManager.lines.clear();
		level->dialogueManager.showingLine = false;
		level->dialogueManager.LoadXMLScript(quest.dialogue_accept);

		level->player.AddQuest(quest_name);
	}

	void decline_quest(GUIButton * button)
	{
		Level * level = (Level *) button->metadata;

		std::string quest_name = level->dialogueManager.currentLine.metadata;
		Quest quest = Quest();
		quest.LoadXMLInfo(quest_name);

		level->dialogueManager.lines.clear();
		level->dialogueManager.showingLine = false;
		level->dialogueManager.LoadXMLScript(quest.dialogue_decline);
	}

	void GUIDialogue::Update(SDL_Renderer * r, std::shared_ptr<Level> level, HUDState * state)
	{
		DialogueManager * dialogueManager = &level->dialogueManager;

		if (state->action_screen == nullptr)
		{
			state->action_screen = new GUIScreen();
			state->action_button_decline = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Decline", (WINDOW_WIDTH - 350) / 2, WINDOW_HEIGHT - HEIGHT - 50 - 20 - 32, 150, 32, &decline_quest));
			state->action_button_decline->metadata = level.get();
			state->action_screen->AddElement(state->action_button_decline);
			state->action_button_accept = std::shared_ptr<GUIButton>(new GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Accept", ((WINDOW_WIDTH - 350) / 2) + 200, WINDOW_HEIGHT - HEIGHT - 50 - 20 - 32, 150, 32, &accept_quest));
			state->action_button_accept->metadata = level.get();
			state->action_screen->AddElement(state->action_button_accept);

			state->action_button_accept->enabled = false;
			state->action_button_decline->enabled = false;
		}

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
			if (state->cached_character_texture == nullptr || dialogueManager->currentLine.character != state->cached_character)
			{
				if (state->cached_character_texture != nullptr)
				{
					SDL_DestroyTexture(state->cached_character_texture);
				}

				std::string character = dialogueManager->currentLine.character;

				SDL_Surface * character_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ GUI_FONT_NAME, 18 }), character.c_str(), { 0, 0, 0, 255 }, WIDTH - (10 * 2));
				state->cached_character_texture = SDL_CreateTextureFromSurface(r, character_surface);

				state->cached_character_rect = { 0, 0, 0, 0 };
				SDL_QueryTexture(state->cached_character_texture, NULL, NULL, &(state->cached_character_rect.w), &(state->cached_character_rect.h));

				SDL_FreeSurface(character_surface);

				state->cached_character = character;
			}

			if (state->cached_text_texture == nullptr || dialogueManager->currentLine.text != state->cached_text)
			{
				if (state->cached_text_texture != nullptr)
				{
					SDL_DestroyTexture(state->cached_text_texture);
				}

				std::string text = dialogueManager->currentLine.text;

				SDL_Surface * text_surface = TTF_RenderText_Blended_Wrapped(Content::GetFont({ GUI_FONT_NAME, 18 }), text.c_str(), { 0, 0, 0, 255 }, WIDTH - (10 * 2));
				state->cached_text_texture = SDL_CreateTextureFromSurface(r, text_surface);

				state->cached_text_rect = { 0, 0, 0, 0 };
				SDL_QueryTexture(state->cached_text_texture, NULL, NULL, &(state->cached_text_rect.w), &(state->cached_text_rect.h));

				SDL_FreeSurface(text_surface);

				state->cached_text = text;

				// also use this time to update the buttons
				state->action_button_accept->enabled = false;
				state->action_button_decline->enabled = false;
				if (dialogueManager->currentLine.special == DialogueLineSpecial::QuestPromptLine)
				{
					state->action_button_accept->enabled = true;
					state->action_button_decline->enabled = true;
				}
			}

			if (Input::IsButtonReleased(Button::ADVANCE_DIALOGUE))
			{
				if (dialogueManager->currentLine.special == DialogueLineSpecial::NormalLine)
				{
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
				else if (dialogueManager->currentLine.special == DialogueLineSpecial::CreditsNextLine)
				{
					GUIManager::current_screen = &GUIManager::credits;
				}
			}

			state->action_screen->Update(r);
		}
	}

	void GUIDialogue::Draw(SDL_Renderer * r, std::shared_ptr<Level> level, HUDState * state)
	{
		DialogueManager * dialogueManager = &level->dialogueManager;

		if (dialogueManager->showingLine)
		{
			SDL_Rect frame_rect = { 50, WINDOW_HEIGHT - HEIGHT - 50, WIDTH, HEIGHT };
			GUIHelper::DrawFrame(r, frame_rect, GUIHelper::FRAME_BROWN_PAPER);
			bool have_character = false;
			if (state->cached_character_texture != nullptr && dialogueManager->currentLine.character != "")
			{
				have_character = true;
				state->cached_character_rect.x = frame_rect.x + 10;
				state->cached_character_rect.y = frame_rect.y + 10;
				SDL_RenderCopy(r, state->cached_character_texture, NULL, &state->cached_character_rect);
			}
			if (state->cached_text_texture != nullptr)
			{
				state->cached_text_rect.x = frame_rect.x + 10;
				state->cached_text_rect.y = frame_rect.y + 10 + (have_character ? (18 + 5) : 0);
				SDL_RenderCopy(r, state->cached_text_texture, NULL, &state->cached_text_rect);
			}
			if (state->cached_instruction_texture != nullptr && (dialogueManager->currentLine.special == DialogueLineSpecial::NormalLine || dialogueManager->currentLine.special == DialogueLineSpecial::CreditsNextLine))
			{
				state->cached_instruction_rect.x = frame_rect.x + 10;
				state->cached_instruction_rect.y = frame_rect.y + (frame_rect.h - state->cached_instruction_rect.h - 10);
				SDL_RenderCopy(r, state->cached_instruction_texture, NULL, &state->cached_instruction_rect);
			}

			state->action_screen->Draw(r);
		}
	}
}