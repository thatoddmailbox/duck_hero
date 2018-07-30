#ifndef _WORKING_MACHINE_HPP
#define _WORKING_MACHINE_HPP

#include "entity.hpp"

#include <SDL.h>

namespace duckhero
{
	class WorkingMachine : public Entity
	{
	private:
		SDL_Texture * _texture;
	public:
		bool facing_right;

		WorkingMachine();
		WorkingMachine(const WorkingMachine& other);
		WorkingMachine& operator=(const WorkingMachine& other);
		~WorkingMachine();

		std::string GetSpritePath() override;

		SDL_Rect GetCollisionBox(int x, int y) override;

		bool CanInteract() override;
		void Interact(void * level_screen_pointer) override;
		void Update() override;
		void Draw(SDL_Renderer * r, int x_offset, int y_offset) override;
	};
}

#endif