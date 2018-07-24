#ifndef _GUI_SHOP_HPP
#define _GUI_SHOP_HPP

#include <memory>
#include <string>
#include <vector>

#include "consts.hpp"
#include "gui.hpp"
#include "gui_helper.hpp"
#include "gui_prompt.hpp"
#include "shop.hpp"
#include "text_cache.hpp"

namespace duckhero
{
	void shop_close(GUIButton * button);

	class GUIShop
	{
	private:
		TextCache _title_cache = TextCache(GUI_FONT_NAME, 18, { 0, 0, 0, 255 }, GUI_SHOP_WIDTH);
		TextCache _desc_cache = TextCache(GUI_FONT_NAME, 16, { 0, 0, 0, 255 }, GUI_SHOP_WIDTH);
		int _coins;
	public:
		GUIButton close = GUIButton(GUIButtonStyle::OldDarkBrownStyle, "Close", WINDOW_WIDTH - 150, WINDOW_HEIGHT - 32, 150, 32, &shop_close);
		std::shared_ptr<GUIPrompt> prompt;
		SDL_Rect rect;
		Shop shop;
		std::vector<GUIButton> buttons;

		GUIShop(void * level_screen_pointer, std::string shop_name);
		void BuyItem(void * level_screen_pointer, int index);
		void Update(SDL_Renderer * r);
		void Draw(SDL_Renderer * r);
	};
}

#endif