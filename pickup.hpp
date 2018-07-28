#ifndef _PICKUP_HPP
#define _PICKUP_HPP

#include <string>
#include <vector>

#include "content.hpp"
#include "entity.hpp"
#include "quest.hpp"

namespace duckhero
{
	struct PickupInfo
	{
		int x;
		int y;
		std::string map;
	};

	class Pickup : public Entity
	{
	private:
		SDL_Texture * _texture;
	public:
		int item_id;
		bool picked_up;

		Pickup();
		Pickup(const Pickup& other);
		Pickup& operator=(const Pickup& other);
		~Pickup();

		std::string GetSpritePath() override;

		SDL_Rect GetCollisionBox(int x, int y) override;

		bool CanInteract() override;
		void Interact(void * level_screen_pointer) override;
		void Update() override;
		void Draw(SDL_Renderer * r, int x_offset, int y_offset) override;
	};
}

#endif