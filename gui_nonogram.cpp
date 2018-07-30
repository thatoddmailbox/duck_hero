#include "gui_nonogram.hpp"

namespace duckhero
{
	SDL_Rect GUINonogram::GetCenterRectForNonogram(SDL_Rect& container, Nonogram * n)
	{
		int width = (GUI_NONOGRAM_CELL_SIZE * n->width);
		int height = (GUI_NONOGRAM_CELL_SIZE * n->height);
		return { container.x + ((container.w - width) / 2), container.y + ((container.h - height) / 2), container.w, container.h };
	}

	void GUINonogram::Update(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect)
	{
		SDL_Rect mouse_rect = Input::GetMouseRect();
		if (SDL_IntersectRect(&rect, &mouse_rect, NULL))
		{
			MouseState mouse_state = Input::GetMouseState();
			if (mouse_state.buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				int mouse_x = mouse_rect.x - rect.x;
				int mouse_y = mouse_rect.y - rect.y;

				int cell_x = mouse_x / GUI_NONOGRAM_CELL_SIZE;
				int cell_y = mouse_y / GUI_NONOGRAM_CELL_SIZE;

				
			}
		}
	}

	void GUINonogram::Draw(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect)
	{
		// fill in the whole thing as a white square
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderFillRect(r, &rect);

		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		for (int x = 0; x < n->width; x++)
		{
			for (int y = 0; y < n->height; y++)
			{
				SDL_Rect cell_rect = { rect.x + (x * GUI_NONOGRAM_CELL_SIZE), rect.y + (y * GUI_NONOGRAM_CELL_SIZE), GUI_NONOGRAM_CELL_SIZE, GUI_NONOGRAM_CELL_SIZE };
				if (n->data[x][y] == NonogramCell::Filled)
				{
					SDL_RenderDrawRect(r, &cell_rect);
				}
				else
				{
					SDL_RenderFillRect(r, &cell_rect);
				}
			}			
		}
	}
}