#include "pickup.hpp"

#include "gui_level.hpp"

namespace duckhero
{
	Pickup::Pickup() : Entity()
	{
		item_id = 0;
		picked_up = false;

		_texture = nullptr;
	}

	Pickup::Pickup(const Pickup& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		item_id = other.item_id;
		picked_up = other.picked_up;

		_texture = nullptr; // don't copy _texture!
	}

	Pickup& Pickup::operator=(const Pickup& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		item_id = other.item_id;
		picked_up = other.picked_up;

		_texture = nullptr; // don't copy _texture!
		return *this;
	}

	Pickup::~Pickup()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
		}
	}

	std::string Pickup::GetSpritePath()
	{
		return "items/" + std::to_string(item_id) + ".png";
	}

	SDL_Rect Pickup::GetCollisionBox(int x, int y)
	{
		if (picked_up)
		{
			return { 0, 0, 0, 0 };
		}
		else
		{
			// totally not a hack
			if (item_id == 6)
			{
				return { x + 9, y + 1, 14, 30 };
			}
			else if (item_id == 12)
			{
				return { x , y + 8, TILE_WIDTH, 16 };
			}
			else
			{
				return Entity::GetCollisionBox(x, y);
			}
		}
	}

	bool Pickup::CanInteract()
	{
		return !picked_up;
	}

	void Pickup::Interact(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;
		level_screen->GetLevel()->player.items.push_back(Item(item_id));
		picked_up = true;
		in_range = false;

		PickupInfo info;
		info.x = x;
		info.y = y;
		info.map = level_screen->GetLevel()->map_name;
		level_screen->GetLevel()->player.pickups.push_back(info);
	}

	void Pickup::Update()
	{
		if (picked_up)
		{
			return;
		}

		Entity::Update();
	}

	void Pickup::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{
		if (picked_up)
		{
			return;
		}

		Entity::Draw(r, x_offset, y_offset);

		if (!_texture)
		{
			_texture = SDL_CreateTextureFromSurface(r, Content::GetBitmap(GetSpritePath()));
		}

		SDL_Rect dst_rect = { x_offset + x, y_offset + y, 32, 32 };
		SDL_RenderCopy(r, _texture, NULL, &dst_rect);
	}
}