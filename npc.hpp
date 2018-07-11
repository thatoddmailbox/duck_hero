#ifndef _NPC_HPP
#define _NPC_HPP

#include <string>

#include "content.hpp"
#include "entity.hpp"

namespace duckhero
{
	class NPC : public Entity
	{
	private:
		SDL_Texture * _texture;
	public:
		std::string name;

		NPC();
		NPC(const NPC& other);
		NPC& operator=(const NPC& other);
		~NPC();

		std::string GetSpritePath() override;

		SDL_Rect GetCollisionBox(int x, int y) override;

		bool LoadXMLInfo(std::string path);

		void Interact(void * level) override;
		void Update() override;
		void Draw(SDL_Renderer * r, int x_offset, int y_offset) override;
	};
}

#endif