#ifndef _SIGN_HPP
#define _SIGN_HPP

#include <string>
#include <vector>

#include "content.hpp"
#include "entity.hpp"

namespace duckhero
{
	class Sign : public Entity
	{
	private:
		SDL_Texture * _texture;
	public:
		std::string text;

		Sign();
		Sign(const Sign& other);
		Sign& operator=(const Sign& other);
		~Sign();

		std::string GetSpritePath() override;

		SDL_Rect GetCollisionBox(int x, int y) override;

		bool CanInteract() override;
		void Interact(void * level_screen_pointer) override;
		void Update() override;
		void Draw(SDL_Renderer * r, int x_offset, int y_offset) override;
	};
}

#endif