#include "gui_credits.hpp"

namespace duckhero
{
	bool GUICredits::Update(SDL_Renderer * r)
	{
		return false;
	}

	void GUICredits::Draw(SDL_Renderer * r)
	{
		SDL_Rect window_rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };

		SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
		SDL_RenderFillRect(r, &window_rect);

		_text_cache.Draw(r, "Duck Hero\n\nwow credits", 10, 10);
	}

	void GUICredits::HandleAction()
	{

	}
}