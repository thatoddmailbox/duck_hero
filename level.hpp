#ifndef _LEVEL_H
#define _LEVEL_H

#include <cstdlib>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "physfs.h"

#include "external/pugixml.hpp"

#include "consts.hpp"
#include "dialogue.hpp"
#include "entity.hpp"
#include "log.hpp"
#include "npc.hpp"
#include "spritesheet.hpp"
#include "player.hpp"

namespace duckhero
{
	enum CollisionMode
	{
		NONE = 0,
		FULL = 1,
		BOTTOM_HALF = 2,
		TOP_HALF = 3
	};

	class Tile
	{
	public:
		int id;
		Spritesheet * sheet;
	};

	class Layer
	{
	private:
		void copy_into_data_from(const Layer& other);
	public:
		Layer();
		Layer(const Layer& other);
		Layer& operator=(const Layer& other);
		~Layer();

		bool IsFixedBottom();
		void Draw(SDL_Renderer * r, int x_offset, int y_offset, int start_y, int end_y);

		std::string name;
		int width, height;
		Tile ** data;
	};

	class Level
	{
	private:
		void copy_into_data_from(const Level& other);
	public:
		std::vector<Layer> layers;
		std::vector<std::shared_ptr<Entity>> entities;
		int width, height;
		Player player;
		DialogueManager dialogueManager;
		CollisionMode ** collision_map;

		Level();
		Level(const Level& other);
		Level& operator=(const Level& other);
		~Level();

		bool LoadFromFile(std::string path);

		bool TryInteract();
		bool TryMoveEntity(Entity * e, int x_offset, int y_offset);
		SDL_Rect GetCollisionBoxForTile(int x, int y);

		void Draw(SDL_Renderer * r, int x_offset, int y_offset);
	};
}

#endif