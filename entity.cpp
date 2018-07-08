#include "entity.hpp"

namespace duckhero
{
	SDL_Rect Entity::GetCollisionBox(int x, int y)
	{
		return { x, y, TILE_WIDTH, TILE_HEIGHT };
	}

	void Entity::Update()
	{

	}

	void Entity::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{

	}
}