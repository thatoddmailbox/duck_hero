#include "working_machine.hpp"

#include "gui_level.hpp"

namespace duckhero
{
	WorkingMachine::WorkingMachine() : Entity()
	{
		facing_right = false;

		_texture = nullptr;
	}

	WorkingMachine::WorkingMachine(const WorkingMachine& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		facing_right = other.facing_right;

		_texture = nullptr; // don't copy _texture!
	}

	WorkingMachine& WorkingMachine::operator=(const WorkingMachine& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		facing_right = other.facing_right;

		_texture = nullptr; // don't copy _texture!
		return *this;
	}

	WorkingMachine::~WorkingMachine()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
		}
	}

	std::string WorkingMachine::GetSpritePath()
	{
		if (facing_right)
		{
			return "tiles/working_right.png";
		}
		else
		{
			return "tiles/working_left.png";
		}
	}

	SDL_Rect WorkingMachine::GetCollisionBox(int x, int y)
	{
		if (facing_right)
		{
			return { x, y, 22, TILE_HEIGHT };
		}
		else
		{
			return { x + (32 - 22), y, 22, TILE_HEIGHT };
		}
	}

	bool WorkingMachine::CanInteract()
	{
		return true;
	}

	void WorkingMachine::Interact(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;

		level_screen->work = std::shared_ptr<GUIWork>(new GUIWork(level_screen_pointer));
	}

	void WorkingMachine::Update()
	{
		Entity::Update();
	}

	void WorkingMachine::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{
		Entity::Draw(r, x_offset, y_offset);

		if (!_texture)
		{
			_texture = SDL_CreateTextureFromSurface(r, Content::GetBitmap(GetSpritePath()));
		}

		SDL_Rect dst_rect = { x_offset + x, y_offset + y, 32, 32 };
		SDL_RenderCopy(r, _texture, NULL, &dst_rect);
	}
}