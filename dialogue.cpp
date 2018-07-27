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

	bool DialogueManager::LoadXMLScript(std::string name)
	{
		std::string full_path = "dialogues/" + name + ".xml";

		// read the file into a string
		PHYSFS_File * f = PHYSFS_openRead(full_path.c_str());
		PHYSFS_sint64 size = PHYSFS_fileLength(f);
		char * buffer = (char *) malloc(size + 1);
		buffer[size] = '\0';
		PHYSFS_readBytes(f, buffer, size);
		PHYSFS_close(f);

		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_string(buffer);

		bool returnValue = true;
		if (result)
		{
			pugi::xml_node dialogue = doc.child("dialogue");

			for (pugi::xml_node line : dialogue.children("line"))
			{
				std::string character = std::string(line.child_value("character"));
				std::string text = std::string(line.child_value("text"));

				if (character == "$PLAYER")
				{
					character = "Ducky";
				}

				AddLine({ character, text, DialogueLineSpecial::NormalLine, "" });
			}
		}
		else
		{
			returnValue = false;
		}

		free(buffer);
		return returnValue;
	}
}