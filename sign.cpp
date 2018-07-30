#include "sign.hpp"

#include "gui_level.hpp"

namespace duckhero
{
	Sign::Sign() : Entity()
	{
		text = "";

		_texture = nullptr;
	}

	Sign::Sign(const Sign& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;
		
		text = other.text;

		_texture = nullptr; // don't copy _texture!
	}

	Sign& Sign::operator=(const Sign& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;
		
		text = other.text;

		_texture = nullptr; // don't copy _texture!
		return *this;
	}

	Sign::~Sign()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
		}
	}

	std::string Sign::GetSpritePath()
	{
		return "tiles/sign.png";
	}

	SDL_Rect Sign::GetCollisionBox(int x, int y)
	{
		return Entity::GetCollisionBox(x, y);
	}

	bool Sign::CanInteract()
	{
		return true;
	}

	void Sign::Interact(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;
		level_screen->GetLevel()->dialogueManager.AddLine({ "Sign", text });
	}

	void Sign::Update()
	{
		Entity::Update();
	}

	void Sign::Draw(SDL_Renderer * r, int x_offset, int y_offset)
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