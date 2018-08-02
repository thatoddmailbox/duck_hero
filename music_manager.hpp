#ifndef _MUSIC_MANAGER_HPP
#define _MUSIC_MANAGER_HPP

#include <string>

#include <SDL.h>
#include <SDL_mixer.h>

#include "content.hpp"

namespace duckhero
{
	class MusicManager
	{
	public:
		static bool loaded;
		static std::string current_track;

		static bool Init();
		static void PlayBackground(std::string new_track);
	};
}

#endif