#include "entity.hpp"

namespace duckhero
{
	std::string Entity::GetSpritePath()
	{
		return "";
	}

	SDL_Rect Entity::GetCollisionBox(int x, int y)
	{
		return { x, y, TILE_WIDTH, TILE_HEIGHT };
	}

	bool Entity::CanInteract()
	{
		return false;
	}

	void Entity::Interact(void * level)
	{

	}

	void Entity::Update()
	{

	}

	void Entity::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{

	}
}