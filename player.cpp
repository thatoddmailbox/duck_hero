#include "player.hpp"

namespace duckhero
{
	Player::Player() : Entity()
	{
		coins = 0;

		current_quests = std::vector<std::string>();
		completed_quests = std::vector<std::string>();
		doors = std::vector<DoorInfo>();
		items = std::vector<Item>();
		pickups = std::vector<PickupInfo>();

		walking = false;
		animation_frame = 0;
		animation_timer = 0;
		direction = DIRECTION_DOWN;

		_texture_up = nullptr;
		_texture_down = nullptr;
		_texture_left = nullptr;
		_texture_right = nullptr;
	}

	Player::Player(const Player& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;
		coins = other.coins;

		current_quests = other.current_quests;
		completed_quests = other.completed_quests;
		items = other.items;

		walking = other.walking;
		animation_frame = other.animation_frame;
		animation_timer = other.animation_timer;
		direction = other.direction;

		_texture_up = nullptr;
		_texture_down = nullptr;
		_texture_left = nullptr;
		_texture_right = nullptr;
	}

	Player& Player::operator=(const Player& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;
		coins = other.coins;

		current_quests = other.current_quests;
		completed_quests = other.completed_quests;
		items = other.items;

		walking = other.walking;
		animation_frame = other.animation_frame;
		animation_timer = other.animation_timer;
		direction = other.direction;

		_texture_up = nullptr;
		_texture_down = nullptr;
		_texture_left = nullptr;
		_texture_right = nullptr;

		return *this;
	}

	Player::~Player()
	{
		if (_texture_up)
		{
			SDL_DestroyTexture(_texture_up);
		}

		if (_texture_down)
		{
			SDL_DestroyTexture(_texture_down);
		}

		if (_texture_left)
		{
			SDL_DestroyTexture(_texture_left);
		}

		if (_texture_right)
		{
			SDL_DestroyTexture(_texture_right);
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

		if (walking)
		{
			animation_timer++;
			if (animation_timer == 10)
			{
				animation_timer = 0;

				animation_frame++;
				if (animation_frame > 1)
				{
					animation_frame = 0;
				}
			}
		}
	}

	void Player::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{
		Entity::Draw(r, x_offset, y_offset);

		SDL_Rect src_rect = { 0, 0, 32, 32 };
		SDL_Texture * tex = nullptr;

		if (direction == DIRECTION_UP)
		{
			if (!_texture_up)
			{
				_texture_up = SDL_CreateTextureFromSurface(r, Content::GetBitmap("characters/ducky_up.png"));
			}
			tex = _texture_up;
		}
		else if (direction == DIRECTION_DOWN)
		{
			if (!_texture_down)
			{
				_texture_down = SDL_CreateTextureFromSurface(r, Content::GetBitmap("characters/ducky_down.png"));
			}
			tex = _texture_down;
		}
		else if (direction == DIRECTION_LEFT)
		{
			if (!_texture_left)
			{
				_texture_left = SDL_CreateTextureFromSurface(r, Content::GetBitmap("characters/ducky_left.png"));
			}
			tex = _texture_left;
		}
		else if (direction == DIRECTION_RIGHT)
		{
			if (!_texture_right)
			{
				_texture_right = SDL_CreateTextureFromSurface(r, Content::GetBitmap("characters/ducky_right.png"));
			}
			tex = _texture_right;
		}

		if (walking)
		{
			src_rect.x = 32 + (animation_frame * 32);
		}

		SDL_Rect dst_rect = { x_offset + x, y_offset + y, 32, 32 };
		SDL_RenderCopy(r, tex, &src_rect, &dst_rect);
	}
}