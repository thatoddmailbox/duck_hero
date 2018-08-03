#include "music_manager.hpp"

namespace duckhero
{
	bool MusicManager::loaded = false;
	std::string MusicManager::current_track = "";

	bool MusicManager::Init()
	{
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
		{
			std::string message = "There was a problem while trying to set up the sound.\n\nThe error was: " + std::string(SDL_GetError()) + ".\n\nYou can still play the game, but sound will not be available.";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                         "Sound error",
                         message.c_str(),
                         NULL);
			return false;
		}
		else
		{
			loaded = true;
			return true;
		}
	}

	void MusicManager::PlayBackground(std::string new_track)
	{
		if (!loaded)
		{
			return;
		}
		if (current_track != new_track)
		{
			Mix_Music * music = Content::GetMusic(new_track + ".ogg");
			Mix_FadeOutMusic(50);
			Mix_FadeInMusic(music, -1, 200);
			current_track = new_track;
		}
	}
}