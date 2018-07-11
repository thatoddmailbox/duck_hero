#include "gui_helper.hpp"

namespace duckhero
{
	void GUIHelper::DrawFrame(SDL_Renderer * r, SDL_Rect location, int top_left_tile)
	{
		SDL_Texture * ui_sheet_texture = Spritesheet::ui.GetTexture(r);
		int tile_w = Spritesheet::ui.tile_w;
		int tile_h = Spritesheet::ui.tile_h;
		int sheet_cols = Spritesheet::ui.cols;

		// top left tile
		SDL_Rect top_left_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile);
		SDL_Rect top_left_dst_rect = { location.x, location.y, tile_w, tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &top_left_tile_rect, &top_left_dst_rect);

		// top middle tile
		SDL_Rect top_middle_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + 1);
		SDL_Rect top_middle_dst_rect = { location.x + tile_w, location.y, location.w - (tile_w * 2), tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &top_middle_tile_rect, &top_middle_dst_rect);

		// top right tile
		SDL_Rect top_right_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + 2);
		SDL_Rect top_right_dst_rect = { location.x + (location.w - tile_w), location.y, tile_w, tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &top_right_tile_rect, &top_right_dst_rect);

		// middle left tile
		SDL_Rect middle_left_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + sheet_cols);
		SDL_Rect middle_left_dst_rect = { location.x, location.y + tile_h, tile_w, location.h - tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &middle_left_tile_rect, &middle_left_dst_rect);

		// middle middle tile
		SDL_Rect middle_middle_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + sheet_cols + 1);
		SDL_Rect middle_middle_dst_rect = { location.x + tile_w, location.y + tile_h, location.w - (tile_w * 2), location.h - tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &middle_middle_tile_rect, &middle_middle_dst_rect);

		// middle right tile
		SDL_Rect middle_right_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + sheet_cols + 2);
		SDL_Rect middle_right_dst_rect = { location.x + (location.w - tile_w), location.y + tile_h, tile_w, location.h - tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &middle_right_tile_rect, &middle_right_dst_rect);

		// bottom left tile
		SDL_Rect bottom_left_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + (sheet_cols * 2));
		SDL_Rect bottom_left_dst_rect = { location.x, location.y + (location.h - tile_h), tile_w, tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &bottom_left_tile_rect, &bottom_left_dst_rect);

		// bottom middle tile
		SDL_Rect bottom_middle_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + (sheet_cols * 2) + 1);
		SDL_Rect bottom_middle_dst_rect = { location.x + tile_w, location.y + (location.h - tile_h), location.w - (tile_w * 2), tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &bottom_middle_tile_rect, &bottom_middle_dst_rect);

		// bottom right tile
		SDL_Rect bottom_right_tile_rect = Spritesheet::ui.GetCoordinatesForTile(top_left_tile + (sheet_cols * 2) + 2);
		SDL_Rect bottom_right_dst_rect = { location.x + (location.w - tile_w), location.y + (location.h - tile_h), tile_w, tile_h };
		SDL_RenderCopy(r, ui_sheet_texture, &bottom_right_tile_rect, &bottom_right_dst_rect);
	}
}