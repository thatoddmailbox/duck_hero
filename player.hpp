#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>

#include "content.hpp"
#include "entity.hpp"

namespace duckhero
{
	class Player : public Entity
	{
	private:
		SDL_Texture * _texture;
	public:
		Player();
		Player(const Player& other);
		Player& operator=(const Player& other);
		~Player();

		std::string GetSpritePath();

		SDL_Rect GetCollisionBox(int x, int y);

		void Update();
		void Draw(SDL_Renderer * r, int x_offset, int y_offset);
	};
}

#endif