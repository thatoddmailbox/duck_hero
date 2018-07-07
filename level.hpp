#ifndef _LEVEL_H
#define _LEVEL_H

#include <cstdlib>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include "physfs.h"

#include "external/pugixml.hpp"

#include "game.hpp"

namespace duckhero
{
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

		std::string name;
		int width, height;
		Tile ** data;
	};

	class Level
	{
	private:
		
	public:
		std::vector<Layer> layers;
		int width, height;

		Level();
		bool LoadFromFile(std::string path);
		void Draw(SDL_Renderer * r, int x_offset, int y_offset);
	};
}

#endif