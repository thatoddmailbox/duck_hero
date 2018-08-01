#include "gui_nonogram.hpp"

namespace duckhero
{
	TextCache GUINonogram::_hint_cache = TextCache(GUI_FONT_NAME, 28, { 0, 0, 0, 255 }, 600);

	SDL_Rect GUINonogram::GetCenterRectForNonogram(SDL_Rect& container, Nonogram * n)
	{
		int width = (GUI_NONOGRAM_CELL_SIZE * n->width);
		int height = (GUI_NONOGRAM_CELL_SIZE * n->height);
		return { container.x + ((container.w - width) / 2), container.y + ((container.h - height) / 2), width, height };
	}

	bool GUINonogram::Update(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect)
	{
		SDL_Rect mouse_rect = Input::GetMouseRect();
		if (mouse_rect.x >= rect.x && mouse_rect.x <= (rect.x + rect.w) && mouse_rect.y >= rect.y && mouse_rect.y <= (rect.y + rect.h))
		{
			MouseState mouse_state = Input::GetMouseState();
			if (mouse_state.buttons & (SDL_BUTTON(SDL_BUTTON_LEFT) | SDL_BUTTON(SDL_BUTTON_RIGHT)))
			{
				if (!n->mouse_down)
				{
					int mouse_x = mouse_rect.x - rect.x;
					int mouse_y = mouse_rect.y - rect.y;

					int cell_x = mouse_x / GUI_NONOGRAM_CELL_SIZE;
					int cell_y = mouse_y / GUI_NONOGRAM_CELL_SIZE;

					bool is_left_button = (mouse_state.buttons & SDL_BUTTON(SDL_BUTTON_LEFT));

					if (n->data[cell_x][cell_y] == NonogramCell::Filled || n->data[cell_x][cell_y] == NonogramCell::Flagged)
					{
						n->data[cell_x][cell_y] = NonogramCell::Empty;
					}
					else
					{
						if (is_left_button)
						{
							n->data[cell_x][cell_y] = NonogramCell::Filled;
						}
						else
						{
							n->data[cell_x][cell_y] = NonogramCell::Flagged;
						}
					}

					n->mouse_down = true;

					return n->IsSolved();
				}
			}
			else
			{
				n->mouse_down = false;
			}
		}

		return false;
	}

	void GUINonogram::Draw(SDL_Renderer * r, Nonogram * n, SDL_Rect& rect)
	{
		// fill in the whole thing as a white square
		SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
		SDL_RenderFillRect(r, &rect);

		// draw cells
		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		for (int x = 0; x < n->width; x++)
		{
			for (int y = 0; y < n->height; y++)
			{
				SDL_Rect cell_rect = { rect.x + (x * GUI_NONOGRAM_CELL_SIZE), rect.y + (y * GUI_NONOGRAM_CELL_SIZE), GUI_NONOGRAM_CELL_SIZE, GUI_NONOGRAM_CELL_SIZE };
				if (n->data[x][y] == NonogramCell::Filled)
				{
					SDL_RenderFillRect(r, &cell_rect);
				}
				else
				{
					SDL_RenderDrawRect(r, &cell_rect);
					if (n->data[x][y] == NonogramCell::Flagged)
					{
						SDL_RenderDrawLine(r, cell_rect.x, cell_rect.y, cell_rect.x + cell_rect.w, cell_rect.y + cell_rect.h);
						SDL_RenderDrawLine(r, cell_rect.x + cell_rect.w, cell_rect.y, cell_rect.x, cell_rect.y + cell_rect.h);
					}
				}
			}			
		}

		// draw column hints
		int x = 0;
		for (std::vector<int>& column_hints : n->horizontal_hints)
		{
			int i = 0;
			for (int& hint_number : column_hints)
			{
				std::string hint_string = std::to_string(hint_number);
				SDL_Rect hint_rect = _hint_cache.MeasureText(r, hint_string);

				int hint_x = rect.x + (x * GUI_NONOGRAM_CELL_SIZE) + ((GUI_NONOGRAM_CELL_SIZE - hint_rect.w) / 2);
				int hint_y = rect.y - ((column_hints.size() - i) * (hint_rect.h + 4));

				_hint_cache.Draw(r, hint_string, hint_x, hint_y);

				i++;
			}
			x++;
		}

		// draw row hints
		int y = 0;
		for (std::vector<int>& row_hints : n->vertical_hints)
		{
			int i = 0;
			for (int& hint_number : row_hints)
			{
				std::string hint_string = std::to_string(hint_number);
				SDL_Rect hint_rect = _hint_cache.MeasureText(r, hint_string);

				int hint_x = rect.x - ((row_hints.size() - i) * (hint_rect.w + 4));
				int hint_y = rect.y + (y * GUI_NONOGRAM_CELL_SIZE) + ((GUI_NONOGRAM_CELL_SIZE - hint_rect.h) / 2);

				_hint_cache.Draw(r, hint_string, hint_x, hint_y);

				i++;
			}
			y++;
		}
	}
}