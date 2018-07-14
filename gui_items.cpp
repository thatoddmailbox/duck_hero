#include "gui_items.hpp"

namespace duckhero
{
	GUIItems::GUIItems(std::shared_ptr<Level> in_level, SDL_Rect in_rect)
	{
		GUIScreen::GUIScreen();

		level = in_level;
		_rect = in_rect;
	}

	void GUIItems::Update(SDL_Renderer * r)
	{
		GUIScreen::Update(r);
	}

	void GUIItems::Draw(SDL_Renderer * r)
	{
		GUIScreen::Draw(r);

		int current_y = _rect.y;
		for (Item& i : level->player.items)
		{
			ItemInfo info = ItemManager::items[i.id];

			SDL_Rect name_rect = _title_cache.Draw(r, info.name, _rect.x, current_y);
			current_y += name_rect.h;

			current_y += 18;
		}

		if (level->player.items.size() == 0)
		{
			_title_cache.Draw(r, "You have no items!", _rect.x, _rect.y);
		}
	}
}