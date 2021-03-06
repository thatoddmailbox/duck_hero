#include "spritesheet.hpp"

namespace duckhero
{
	Spritesheet Spritesheet::ui = Spritesheet("tiles/ui.png", 30, 33, 16, 16, 2);

	Spritesheet Spritesheet::base = Spritesheet("tiles/base.png", 57, 31, 16, 16, 1);
	Spritesheet Spritesheet::characters = Spritesheet("tiles/characters.png", 57, 12, 16, 16, 1);
	Spritesheet Spritesheet::city = Spritesheet("tiles/city.png", 37, 28, 16, 16, 1);
	Spritesheet Spritesheet::dungeon = Spritesheet("tiles/dungeon.png", 30, 19, 16, 16, 1);
	Spritesheet Spritesheet::indoor = Spritesheet("tiles/indoor.png", 27, 18, 16, 16, 1);
	Spritesheet Spritesheet::duck = Spritesheet("tiles/duck.png", 3, 1, 16, 16, 0);

	Spritesheet::Spritesheet(std::string in_path, int in_cols, int in_rows, int in_tile_w, int in_tile_h, int in_margin)
	{
		path = in_path;
		cols = in_cols;
		rows = in_rows;
		tile_w = in_tile_w;
		tile_h = in_tile_h;
		margin = in_margin;
		_texture = nullptr;
	}

	SDL_Rect Spritesheet::GetCoordinatesForTile(int x, int y)
	{
		return SDL_Rect{ x * (tile_w + margin), y * (tile_h + margin), tile_w, tile_h };
	}

	SDL_Rect Spritesheet::GetCoordinatesForTile(int id)
	{
		int x = (id % cols);
		int y = (id / cols);
		return GetCoordinatesForTile(x, y);
	}

	SDL_Texture * Spritesheet::GetTexture(SDL_Renderer * r)
	{
		if (_texture == nullptr)
		{
			_texture = SDL_CreateTextureFromSurface(r, Content::GetBitmap(path));
		}
		return _texture;
	}
}