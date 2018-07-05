#include "spritesheet.hpp"

namespace duckhero
{
	Spritesheet Spritesheet::ui = Spritesheet::Spritesheet("tiles/ui.png", 30, 33, 16, 16, 2);

	Spritesheet::Spritesheet(std::string in_path, int in_cols, int in_rows, int in_tile_w, int in_tile_h, int in_margin)
	{
		path = in_path;
		cols = in_cols;
		rows = in_rows;
		tile_w = in_tile_w;
		tile_h = in_tile_h;
		margin = in_margin;
	}

	SDL_Rect Spritesheet::GetCoordinatesForTile(int x, int y)
	{
		return SDL_Rect{ x * (tile_w + margin), y * (tile_h + margin), tile_w, tile_h };
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