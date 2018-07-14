#include "player.hpp"

namespace duckhero
{
	Player::Player()
	{
		x = y = 0;
		health = 20;
		_texture = nullptr;
	}

	Player::Player(const Player& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;
		_texture = nullptr; // don't copy _texture!
	}

	Player& Player::operator=(const Player& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;
		_texture = nullptr; // don't copy _texture!
		return *this;
	}

	Player::~Player()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
		}
	}

	std::string Player::GetSpritePath()
	{
		return "characters/ducky.png";
	}

	SDL_Rect Player::GetCollisionBox(int x, int y)
	{
		return { x + 4, y + (TILE_HEIGHT / 2), TILE_WIDTH - (4 * 2), (TILE_HEIGHT / 2) };
	}

	void Player::AddQuest(std::string quest_name)
	{
		current_quests.push_back(quest_name);
	}

	void Player::Update()
	{
		Entity::Update();
	}

	void Player::Draw(SDL_Renderer * r, int x_offset, int y_offset)
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