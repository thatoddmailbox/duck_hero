#include "npc.hpp"

#include "level.hpp"

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
		_texture = nullptr; // don't copy _texture!
	}

	NPC& NPC::operator=(const NPC& other)
	{
		x = other.x;
		y = other.y;
		health = other.health;
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
		}
		else
		{
			returnValue = false;
		}

		free(buffer);
		return returnValue;
	}

	void NPC::Interact(void * level)
	{
		Level * l = (Level *) level;
		l->dialogueManager.LoadXMLScript("intro");
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