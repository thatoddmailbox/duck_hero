#include "gui_shop.hpp"

#include "gui_level.hpp"

namespace duckhero
{
	static void shop_buy(GUIButton * button)
	{
		GUIShop * gui_shop = (GUIShop *) button->metadata;
		GUILevelScreen * level_screen = (GUILevelScreen *) button->metadata_2;
		int index = button->metadata_3;
		gui_shop->BuyItem(level_screen, index);
	}

	void shop_close(GUIButton * button)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) button->metadata;
		level_screen->shop = nullptr;
	}

	GUIShop::GUIShop(void * level_screen_pointer, std::string shop_name)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;

		shop.LoadXMLInfo(shop_name);
		close.metadata = level_screen_pointer;
		rect = { (WINDOW_WIDTH - GUI_SHOP_WIDTH) / 2, (WINDOW_HEIGHT - GUI_SHOP_HEIGHT) / 2, GUI_SHOP_WIDTH, GUI_SHOP_HEIGHT };

		_coins = level_screen->GetLevel()->player.coins;

		int i = 0;
		int current_y = rect.y + 10;
		for (ShopItem& listing : shop.items)
		{
			ItemInfo item = ItemManager::items[listing.item_id];

			GUIButton buy = GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Buy", rect.x + rect.w - 100 - 10, current_y + 5, 100, 32, &shop_buy);
			buy.metadata = this;
			buy.metadata_2 = level_screen;
			buy.metadata_3 = i;
			buttons.push_back(buy);

			current_y += (18 + 16 + 2 + 10);
			i++;
		}
	}

	void GUIShop::BuyItem(void * level_screen_pointer, int index)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;
		ShopItem item = shop.items[index];

		level_screen->GetLevel()->player.coins -= item.price;
		level_screen->GetLevel()->player.items.push_back(Item(item.item_id));
		_coins = level_screen->GetLevel()->player.coins;
	}

	void GUIShop::Update(SDL_Renderer * r)
	{
		for (GUIButton& button : buttons)
		{
			button.Update(r);
		}

		close.Update(r);
	}

	void GUIShop::Draw(SDL_Renderer * r)
	{
		GUIHelper::DrawMenuOverlay(r);
		GUIHelper::DrawFrame(r, rect, GUIHelper::FRAME_BROWN_PAPER);

		int i = 0;
		int current_y = rect.y + 10;
		for (ShopItem& listing : shop.items)
		{
			ItemInfo item = ItemManager::items[listing.item_id];

			if (_coins >= listing.price)
			{
				buttons[i].Draw(r);
			}
			else
			{
				_desc_cache.Draw(r, "Too expensive", rect.x + rect.w - 104 - 10, current_y + (19 / 2));
			}

			SDL_Rect title_rect = _title_cache.Draw(r, item.name + " - " + std::to_string(listing.price) + " gold", rect.x + 10, current_y);
			current_y += title_rect.h;

			SDL_Rect desc_rect = _desc_cache.Draw(r, item.desc, rect.x + 10, current_y);
			current_y += desc_rect.h;

			current_y += 10;
			i++;
		}

		close.Draw(r);
	}
}