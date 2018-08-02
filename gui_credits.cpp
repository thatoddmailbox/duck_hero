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

		_text_cache.Draw(r, "Duck Hero\n\
\n\
Designed by Ducky Quackers\n\
Produced by Dogo\n\
\n\
Art: Some assets were created by Kenney - http://kenney.nl\n\
\n\
Font: Fixedsys Excelsior - http://www.fixedsysexcelsior.com/\n\
\n\
Music: Eric Skiff - Resistor Anthems - Available at http://EricSkiff.com/music\n\
Tracks used: Underclocked, We're the Resistors, HHavok-intro\n\
\n\
Open-source software used:\n\
* SDL - Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>\n\
* SDL_gfx - Copyright (C) 2012-2018 A. Schiffler <aschiffler@ferzkopp.net>\n\
* SDL_image - Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>\n\
* SDL_mixer - Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>\n\
* SDL_ttf - Copyright (C) 2001-2013 Sam Lantinga <slouken@libsdl.org>\n\
* PhysicsFS - Copyright (c) 2001-2012 Ryan C. Gordon and others.\n\
\n\
Thanks for playing!", 10, 10);
	}

	void GUICredits::HandleAction()
	{

	}
}