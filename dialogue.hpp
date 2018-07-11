#ifndef _DIALOGUE_HPP
#define _DIALOGUE_HPP

#include <string>
#include <vector>

#include <SDL.h>

namespace duckhero
{
	struct DialogueLine
	{
		std::string character;
		std::string text;
	};

	class DialogueManager
	{
	public:
		std::vector<DialogueLine> lines;
		DialogueLine currentLine;
		bool showingLine;

		DialogueManager();

		void AddLine(DialogueLine line);
	};
}

#endif