#ifndef _GUI_HPP
#define _GUI_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "content.hpp"
#include "input.hpp"
#include "level.hpp"
#include "spritesheet.hpp"

namespace duckhero
{
	enum GUIButtonStyle
	{
		WhiteStyle = 0,
		YellowStyle = 6,
		GreenStyle = 12,
		OrangeStyle = 18,
		BlueStyle = 24,

		OldWhiteStyle = 480,
		OldGrayStyle = 483,
		OldDarkBrownStyle = 486,
		OldLightBrownStyle = 489
	};

	class GUIElement
	{
	public:
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;
		bool enabled = true;
		void * metadata = nullptr;
		void * metadata_2 = nullptr;
		int metadata_3 = 0;

		virtual bool Update(SDL_Renderer * r) = 0;
		virtual void Draw(SDL_Renderer * r) = 0;
		virtual void HandleAction() = 0;
	};

	class GUIButton : public GUIElement
	{
	private:
		SDL_Texture * _text_texture;
		SDL_Texture * _text_hover_texture;
		SDL_Rect _text_rect;
		SDL_Rect _rect;
		std::string _saved_text;
		bool _hover, _clicked;
	public:
		GUIButtonStyle style;
		std::string text;
		int font_size;
		bool active;
		void (*handler)(GUIButton *);

		GUIButton(GUIButtonStyle in_style, std::string in_text, int in_x, int in_y, int in_w, int in_h, void (*in_handler)(GUIButton *));
		~GUIButton();
		bool Update(SDL_Renderer * r) override;
		void Draw(SDL_Renderer * r) override;
		void HandleAction() override;
	};

	class GUIScreen
	{
	public:
		void AddElement(std::shared_ptr<GUIElement> e);
		virtual void Update(SDL_Renderer * r);
		virtual void Draw(SDL_Renderer * r);

		std::vector<std::shared_ptr<GUIElement>> elements;
	};
}

#endif