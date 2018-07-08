#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <SDL.h>

#include "consts.hpp"

namespace duckhero
{
	class Entity
	{
	public:
		int health;
		int x, y;
		virtual SDL_Rect GetCollisionBox(int x, int y);
		virtual void Update();
		virtual void Draw(SDL_Renderer * r, int x_offset, int y_offset);
	};
}

#endif