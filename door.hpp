#ifndef _DOOR_HPP
#define _DOOR_HPP

#include <string>
#include <vector>

#include "content.hpp"
#include "entity.hpp"

namespace duckhero
{
	struct DoorInfo
	{
		int x;
		int y;
		std::string map;
	};

	class Door : public Entity
	{
	private:
		SDL_Texture * _texture;
	public:
		int key_id;
		bool unlocked;

		Door();
		Door(const Door& other);
		Door& operator=(const Door& other);
		~Door();

		std::string GetSpritePath() override;

		SDL_Rect GetCollisionBox(int x, int y) override;

		bool CanInteract() override;
		void Interact(void * level_screen_pointer) override;
		void Update() override;
		void Draw(SDL_Renderer * r, int x_offset, int y_offset) override;
	};
}

#endif