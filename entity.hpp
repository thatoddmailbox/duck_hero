#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <SDL.h>

namespace duckhero
{
	class Entity
	{
	public:
		int health;
		int x, y;
		virtual void Update();
		virtual void Draw(SDL_Renderer * r, int x_offset, int y_offset);
	};
}

#endif