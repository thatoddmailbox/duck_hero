#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <string>

#include <SDL.h>

#include "consts.hpp"

namespace duckhero
{
	class Entity
	{
	public:
		int health;
		int x, y;
		bool in_range;

		Entity();

		virtual std::string GetSpritePath();
		virtual SDL_Rect GetCollisionBox(int x, int y);
		virtual bool CanInteract();
		virtual void Interact(void * level);
		virtual void Update();
		virtual void Draw(SDL_Renderer * r, int x_offset, int y_offset);
	};
}

#endif