#include "npc.hpp"

#include "level.hpp"
#include "gui_level.hpp"

namespace duckhero
{
	NPC::NPC()
	{
		x = y = 0;
		health = 20;

		_texture = nullptr;
	}

	NPC::NPC(const NPC& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		name = other.name;
		shop_name = other.shop_name;
		quests = other.quests;
		idle = other.idle;

		_texture = nullptr; // don't copy _texture!
	}

	NPC& NPC::operator=(const NPC& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;

		name = other.name;
		shop_name = other.shop_name;
		quests = other.quests;
		idle = other.idle;

		_texture = nullptr; // don't copy _texture!
		return *this;
	}

	NPC::~NPC()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
		}
	}

	std::string NPC::GetSpritePath()
	{
		return "characters/ducky.png";
	}

	SDL_Rect NPC::GetCollisionBox(int x, int y)
	{
		return Entity::GetCollisionBox(x, y);
	}

	bool NPC::LoadXMLInfo(std::string path)
	{
		std::string full_path = "npcs/" + path + ".xml";

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
			pugi::xml_node npc = doc.child("npc");

			name = std::string(npc.child_value("name"));
			shop_name = std::string(npc.child_value("shop"));

			for (pugi::xml_node quest_node : npc.child("quests").children("quest"))
			{
				std::string quest_name = quest_node.text().as_string();
				Quest quest = Quest();
				quest.LoadXMLInfo(quest_name);
				quests.push_back(quest);
			}

			for (pugi::xml_node line_node : npc.child("idle").children("line"))
			{
				std::string line = line_node.text().as_string();
				idle.push_back(line);
			}
		}
		else
		{
			returnValue = false;
		}

		free(buffer);
		return returnValue;
	}

	bool NPC::HasShop()
	{
		return (shop_name != "");
	}

	bool NPC::HasQuests()
	{
		return (quests.size() != 0);
	}

	bool NPC::CanInteract()
	{
		return true;
	}
	
	static void prompt_handle_response(GUIPrompt * prompt, std::string action)
	{
		NPC * npc = (NPC *) prompt->metadata;
		GUILevelScreen * level_screen = (GUILevelScreen *) prompt->metadata_2;
		level_screen->prompt = nullptr;
		if (action == "Browse shop")
		{
			npc->HandleShop(level_screen);
		}
		else if (action == "Talk")
		{
			npc->HandleQuests(level_screen);
		}
	}

	void NPC::Interact(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;
		if (HasQuests() && HasShop())
		{
			// ask for clarification
			std::map<std::string, GUIPromptHandler> actions;
			actions["Browse shop"] = &prompt_handle_response;
			actions["Talk"] = &prompt_handle_response;
			std::shared_ptr<GUIPrompt> ask_prompt = std::shared_ptr<GUIPrompt>(new GUIPrompt("Select an option", actions));
			ask_prompt->metadata = this;
			ask_prompt->metadata_2 = level_screen;
			level_screen->prompt = ask_prompt;
		}
		else if (HasQuests())
		{
			HandleQuests(level_screen);
		}
		else if (HasShop())
		{
			HandleShop(level_screen);
		}
	}

	void NPC::HandleShop(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;
		level_screen->shop = std::shared_ptr<GUIShop>(new GUIShop(level_screen, shop_name));
	}

	void NPC::HandleQuests(void * level_screen_pointer)
	{
		GUILevelScreen * level_screen = (GUILevelScreen *) level_screen_pointer;

		// try giving a quest
		for (Quest& quest : quests)
		{
			if (quest.HasBeenCompleted(level_screen->GetLevel().get()))
			{
				continue;
			}
			if (quest.HasBeenStarted(level_screen->GetLevel().get()))
			{
				if (quest.AllTasksDone(level_screen->GetLevel().get()))
				{
					// yay it's done
					level_screen->GetLevel()->dialogueManager.LoadXMLScript(quest.dialogue_complete);
					// TODO: rewards and stuff
				}
				else
				{
					// make fun of them for not finishing it
					level_screen->GetLevel()->dialogueManager.LoadXMLScript(quest.dialogue_progress);
					return;
				}
			}
			if (quest.AllRequirementsMet(level_screen->GetLevel().get()))
			{
				// give this one
				level_screen->GetLevel()->dialogueManager.LoadXMLScript(quest.dialogue_prompt);
				int last_line_index = level_screen->GetLevel()->dialogueManager.lines.size() - 1;
				level_screen->GetLevel()->dialogueManager.lines[last_line_index].special = DialogueLineSpecial::QuestPromptLine;
				level_screen->GetLevel()->dialogueManager.lines[last_line_index].metadata = quest.name;
				return;
			}
		}

		// just say something random then
		int idle_index = rand() % idle.size();
		level_screen->GetLevel()->dialogueManager.AddLine({ name, idle[idle_index] });
	}

	void NPC::Update()
	{
		Entity::Update();
	}

	void NPC::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{
		Entity::Draw(r, x_offset, y_offset);

		if (!_texture)
		{
			_texture = SDL_CreateTextureFromSurface(r, Content::GetBitmap(GetSpritePath()));
		}

		SDL_Rect dst_rect = { x_offset + x, y_offset + y, 32, 32 };
		SDL_RenderCopy(r, _texture, NULL, &dst_rect);
	}
}