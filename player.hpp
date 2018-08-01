#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <string>
#include <vector>

#include "content.hpp"
#include "consts.hpp"
#include "door.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "pickup.hpp"

namespace duckhero
{
	class Player : public Entity
	{
	private:
		SDL_Texture * _texture_up;
		SDL_Texture * _texture_down;
		SDL_Texture * _texture_left;
		SDL_Texture * _texture_right;
	public:
		std::vector<std::string> current_quests;
		std::vector<std::string> completed_quests;
		std::vector<PickupInfo> pickups;
		std::vector<DoorInfo> doors;
		std::vector<Item> items;
		int coins;

		bool walking;
		int animation_frame;
		int animation_timer;
		int direction;

		Player();
		Player(const Player& other);
		Player& operator=(const Player& other);
		~Player();

		std::string GetSpritePath();

		SDL_Rect GetCollisionBox(int x, int y);

		void AddQuest(std::string quest_name);

		void Update();
		void Draw(SDL_Renderer * r, int x_offset, int y_offset);
	};
}

#endif