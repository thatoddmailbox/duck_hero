#ifndef _SPRITESHEET_HPP
#define _SPRITESHEET_HPP

#include <string>

#include <SDL.h>

#include "content.hpp"

namespace duckhero
{
	class Spritesheet
	{
	private:
		SDL_Texture * _texture;
	public:
		static Spritesheet ui;
		static Spritesheet base;

		Spritesheet(std::string in_path, int in_cols, int in_rows, int in_tile_w, int in_tile_h, int in_margin);

		std::string path;
		int cols, rows;
		int tile_w, tile_h;
		int margin;
		SDL_Rect GetCoordinatesForTile(int x, int y);
		SDL_Rect GetCoordinatesForTile(int id);
		SDL_Texture * GetTexture(SDL_Renderer * r);
	};
}

#endif