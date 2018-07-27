#include "door.hpp"

#include "gui_level.hpp"

namespace duckhero
{
	Door::Door()
	{
		Entity::Entity();

		key_id = 0;
		unlocked = false;

		_texture = nullptr;
	}

	Door::Door(const Door& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		key_id = other.key_id;
		unlocked = other.unlocked;

		_texture = nullptr; // don't copy _texture!
	}

	Door& Door::operator=(const Door& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		key_id = other.key_id;
		unlocked = other.unlocked;

		_texture = nullptr; // don't copy _texture!
		return *this;
	}

	Door::~Door()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
		}
	}

	std::string Door::GetSpritePath()
	{
		return "tiles/door.png";
	}

	SDL_Rect Door::GetCollisionBox(int x, int y)
	{
		if (unlocked)
		{
			return { 0, 0, 0, 0 };
		}
		else
		{
			return Entity::GetCollisionBox(x, y);
		}
	}

	bool Door::CanInteract()
	{
		return !unlocked;
	}

	void Door::Interact(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;

		bool has_key = false;

		for (Item& i : level_screen->GetLevel()->player.items)
		{
			if (i.id == key_id)
			{
				has_key = true;
				break;
			}
		}

		if (!has_key)
		{
			level_screen->GetLevel()->dialogueManager.AddLine({ "", "A key is required to open this door." });
			return;
		}

		ItemInfo key_info = ItemManager::items[key_id];
		
		level_screen->GetLevel()->dialogueManager.AddLine({ "", "You use the " + key_info.name + " to unlock the door." });

		unlocked = true;
	}

	void Door::Update()
	{
		if (unlocked)
		{
			return;
		}

		Entity::Update();
	}

	void Door::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{
		if (unlocked)
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