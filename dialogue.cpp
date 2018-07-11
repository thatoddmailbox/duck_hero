#include "dialogue.hpp"

namespace duckhero
{
	DialogueManager::DialogueManager()
	{
		lines = std::vector<DialogueLine>();
		currentLine = DialogueLine();
		showingLine = false;
	}

	void DialogueManager::AddLine(DialogueLine line)
	{
		lines.push_back(line);
		if (!showingLine)
		{
			currentLine = lines.at(0);
			showingLine = true;
		}
	}
}