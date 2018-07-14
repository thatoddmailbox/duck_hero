#include "level.hpp"

namespace duckhero
{
	Level::Level()
	{
		layers = std::vector<Layer>();
		entities = std::vector<std::shared_ptr<Entity>>();
		width = 0;
		height = 0;
		player = Player();
		dialogueManager = DialogueManager();
		collision_map = nullptr;
	}

	Level::Level(const Level& other)
	{
		layers = other.layers;
		entities = other.entities;
		width = other.width;
		height = other.height;
		player = other.player;
		dialogueManager = other.dialogueManager;
		if (other.collision_map)
		{
			copy_into_data_from(other);
		}
		else
		{
			collision_map = nullptr;
		}
	}

	Level& Level::operator=(const Level& other)
	{
		layers = other.layers;
		entities = other.entities;
		width = other.width;
		height = other.height;
		player = other.player;
		dialogueManager = other.dialogueManager;
		if (other.collision_map)
		{
			copy_into_data_from(other);
		}
		else
		{
			collision_map = nullptr;
		}
		return *this;
	}

	Level::~Level()
	{
		if (collision_map)
		{
			for (int x = 0; x < width; x++)
			{
				free(collision_map[x]);
			}
			free(collision_map);
		}
	}

	void Level::copy_into_data_from(const Level& other)
	{
		collision_map = (CollisionMode **) calloc(other.width, sizeof(CollisionMode *));
		for (int x = 0; x < other.width; x++)
		{
			collision_map[x] = (CollisionMode *) calloc(other.height, sizeof(CollisionMode));
			for (int y = 0; y < other.height; y++)
			{
				collision_map[x][y] = other.collision_map[x][y];
			}
		}
	}

	bool Level::LoadFromFile(std::string path)
	{
		layers = std::vector<Layer>();

		// read the file into a string
		PHYSFS_File * f = PHYSFS_openRead(path.c_str());
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
			pugi::xml_node map = doc.child("map");

			width = map.attribute("width").as_int();
			height = map.attribute("height").as_int();

			// the std::greater<int> at the end sorts the map by descending order, helpful later for comparison to determine the spritesheet of a tile
			std::map<int, Spritesheet *, std::greater<int>> spritesheets;

			int collisionGid = 0;

			// read the tileset information
			for (pugi::xml_node tileset : map.children("tileset"))
			{
				int firstgid = tileset.attribute("firstgid").as_int();

				pugi::xml_node image = tileset.child("image");
				const char * source = image.attribute("source").value();
				if (!source)
				{
					Log::Warning("Level::LoadFromFile", "bad tileset declaration (missing source image?)");
					continue;
				}

				// try and match it to a spritesheet
				Spritesheet * sheet;

				if (strstr(source, "base.png") != nullptr)
				{
					sheet = &Spritesheet::base;
				}
				else if (strstr(source, "characters.png") != nullptr)
				{
					sheet = &Spritesheet::characters;
				}
				else if (strstr(source, "city.png") != nullptr)
				{
					sheet = &Spritesheet::city;
				}
				else if (strstr(source, "dungeon.png") != nullptr)
				{
					sheet = &Spritesheet::dungeon;
				}
				else if (strstr(source, "indoor.png") != nullptr)
				{
					sheet = &Spritesheet::indoor;
				}

				if (strstr(source, "collision.png") != nullptr)
				{
					// skip it, it's not a real tileset
					collisionGid = firstgid;
					continue;
				}

				if (sheet == nullptr)
				{
					Log::Warning("Level::LoadFromFile", "couldn't find spritesheet for tileset!");
					continue;
				}

				spritesheets[firstgid] = sheet;
			}

			// start reading the layers
			for (pugi::xml_node layer_node : map.children("layer"))
			{
				const char * name = layer_node.attribute("name").value();

				if (strncmp(name, "COLLISION", 9) == 0)
				{
					// it's a collision layer

					// clear data that we might already have
					if (collision_map)
					{
						for (int x = 0; x < width; x++)
						{
							free(collision_map[x]);
						}
						free(collision_map);
					}

					// create a new array
					collision_map = (CollisionMode **) calloc(width, sizeof(CollisionMode *));
					for (int x = 0; x < width; x++)
					{
						collision_map[x] = (CollisionMode *) calloc(height, sizeof(CollisionMode));
					}

					// read in tile collision data
					pugi::xml_node data = layer_node.child("data");
					int x = 0;
					int y = 0;
					for (pugi::xml_node tile : data.children("tile"))
					{
						if (tile.attribute("gid"))
						{
							int gid = tile.attribute("gid").as_int();
							int id = gid - collisionGid;
							collision_map[x][y] = static_cast<CollisionMode>(id + 1);
						}

						x++;
						if (x >= width)
						{
							y++;
							x = 0;
						}
					}
					continue;
				}

				// create a new layer object for the layer
				Layer layer;
				layer.name = std::string(name);
				layer.data = (Tile **) calloc(width, sizeof(Tile *));
				layer.width = width;
				layer.height = height;
				
				for (int x = 0; x < width; x++)
				{
					layer.data[x] = (Tile *) calloc(height, sizeof(Tile));
					
					for (int y = 0; y < height; y++)
					{
						layer.data[x][y] = Tile();
						layer.data[x][y].id = -1;
						layer.data[x][y].sheet = nullptr;
					}
				}

				// read the tiles
				pugi::xml_node data = layer_node.child("data");
				int x = 0;
				int y = 0;
				for (pugi::xml_node tile : data.children("tile"))
				{
					if (!tile.attribute("gid"))
					{
						// doesn't exist
						layer.data[x][y] = Tile();
						layer.data[x][y].id = -1;
						layer.data[x][y].sheet = nullptr;

						x++;
						if (x >= width)
						{
							y++;
							x = 0;
						}

						continue;
					}

					int gid = tile.attribute("gid").as_int();
					int id = -1;
					Spritesheet * sheet;

					// find the spritesheet for the tile
					for (std::map<int, Spritesheet *>::iterator iter = spritesheets.begin(); iter != spritesheets.end(); ++iter)
					{
						int currentSheetGid = iter->first;
						Spritesheet * currentSheet = iter->second;
						if (gid > currentSheetGid)
						{
							// found the correct spritesheet, stop now
							sheet = currentSheet;
							id = (gid - currentSheetGid);
							break;
						}
					}

					layer.data[x][y] = Tile();
					layer.data[x][y].id = id;
					layer.data[x][y].sheet = sheet;

					x++;
					if (x >= width)
					{
						y++;
						x = 0;
					}
				}

				layers.push_back(layer);
			}

			// load object groups
			for (pugi::xml_node object_group_node : map.children("objectgroup"))
			{
				const char * name = object_group_node.attribute("name").as_string();
				if (strcmp(name, "NPC") == 0)
				{
					// it's the NPC layer
					for (pugi::xml_node object_node : object_group_node.children("object"))
					{
						int x = object_node.attribute("x").as_int();
						int y = object_node.attribute("y").as_int();
						for (pugi::xml_node property_node : object_node.child("properties").children("property"))
						{
							const char * property_name = property_node.attribute("name").as_string();
							const char * property_value = property_node.attribute("value").as_string();

							if (strcmp(property_name, "npc") == 0)
							{
								NPC * npc = new NPC();
								npc->LoadXMLInfo(std::string(property_value));
								npc->x = (x) * 2;
								npc->y = (y - 16) * 2;
								entities.push_back(std::shared_ptr<Entity>(npc));
							}
						}
					}
				}
				else
				{
					// unknown layer
					Log::Warning("Level::LoadFromFile", "unrecognized object group (incorrect name?)");
					returnValue = false;
				}
			}
		}
		else
		{
			Log::Warning("Level::LoadFromFile", "invalid XML file!");
			returnValue = false;
		}

		free(buffer);

		return returnValue;
	}

	bool Level::TryInteract(void * level_screen_pointer)
	{
		int range = 5;

		SDL_Rect player_box = player.GetCollisionBox(player.x, player.y);
		player_box.x -= range;
		player_box.y -= range;
		player_box.w += (range * 2);
		player_box.h += (range * 2);

		for (std::shared_ptr<Entity>& other_entity : entities)
		{
			SDL_Rect other_box = other_entity->GetCollisionBox(other_entity->x, other_entity->y);
			if (SDL_HasIntersection(&player_box, &other_box))
			{
				// found something
				other_entity->Interact(level_screen_pointer);
				return true;
			}
		}

		return false;
	}

	bool Level::TryMoveEntity(Entity * e, int x_offset, int y_offset)
	{
		int new_x = e->x + x_offset;
		int new_y = e->y + y_offset;
		int tile_x = new_x / TILE_WIDTH;
		int tile_y = new_y / TILE_HEIGHT;

		SDL_Rect entity_box = e->GetCollisionBox(new_x, new_y);

		// TODO: there's probably a smarter way of doing this...this is somewhat brute-forcey
		std::vector<SDL_Rect> tiles_to_check = std::vector<SDL_Rect>();
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x - 1, tile_y - 1));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x - 1, tile_y));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x - 1, tile_y + 1));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x, tile_y - 1));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x, tile_y));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x, tile_y + 1));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x + 1, tile_y - 1));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x + 1, tile_y));
		tiles_to_check.push_back(GetCollisionBoxForTile(tile_x + 1, tile_y + 1));

		for (SDL_Rect tile_to_check : tiles_to_check)
		{
			if (SDL_HasIntersection(&entity_box, &tile_to_check))
			{
				// we can't do this movement!
				return false;
			}
		}

		// are we colliding with any other entities?
		for (std::shared_ptr<Entity>& test_entity : entities)
		{
			SDL_Rect test_box = test_entity->GetCollisionBox(test_entity->x, test_entity->y);
			if (test_entity.get() != e && SDL_HasIntersection(&entity_box, &test_box))
			{
				// we can't do this movement!
				return false;
			}
		}

		// we made it this far, we can move
		e->x += x_offset;
		e->y += y_offset;

		return true;
	}

	SDL_Rect Level::GetCollisionBoxForTile(int x, int y)
	{
		if (x < 0 || x >= width || y < 0 || y >= height)
		{
			return { 0, 0, 0, 0 };
		}
		CollisionMode mode = collision_map[x][y];
		if (mode == CollisionMode::NONE)
		{
			return { 0, 0, 0, 0 };
		}
		else if (mode == CollisionMode::FULL)
		{
			return { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
		}
		else if (mode == CollisionMode::TOP_HALF)
		{
			return { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, (TILE_HEIGHT / 2) };
		}
		else if (mode == CollisionMode::BOTTOM_HALF)
		{
			return { x * TILE_WIDTH, (y * TILE_HEIGHT) + (TILE_HEIGHT / 2), TILE_WIDTH, (TILE_HEIGHT / 2) };
		}

		return { 0, 0, 0, 0 };
	}

	void Level::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{
		// draw the layers up to the player's y
		for (Layer& layer : layers)
		{
			if (layer.IsFixedBottom())
			{
				// it's a ground thing so the player is always above
				layer.Draw(r, x_offset, y_offset, 0, height);
			}
			else
			{
				// draw up to the player
				int player_tile_y = ((player.y - 1) / 32);
				if (player_tile_y < 0)
				{
					player_tile_y = 0;
				}
				layer.Draw(r, x_offset, y_offset, 0, player_tile_y + 1);
			}
		}

		// draw entities
		for (std::shared_ptr<Entity>& e : entities)
		{
			e->Draw(r, x_offset, y_offset);
		}

		// draw the player
		player.Draw(r, x_offset, y_offset);

		// draw the layers up to the player's y
		for (Layer& layer : layers)
		{
			if (!layer.IsFixedBottom())
			{
				// draw after the player
				int player_tile_y = ((player.y - 1) / 32);
				if (player_tile_y < 0)
				{
					player_tile_y = 0;
				}
				layer.Draw(r, x_offset, y_offset, player_tile_y + 1, height);
			}
		}
	}

	Layer::Layer()
	{
		name = "";
		width = 0;
		height = 0;
		data = nullptr;
	}

	Layer::Layer(const Layer& other)
	{
		name = other.name;
		width = other.width;
		height = other.height;
		copy_into_data_from(other);
	}

	Layer& Layer::operator=(const Layer& other)
	{
		name = other.name;
		width = other.width;
		height = other.height;
		copy_into_data_from(other);
		return *this;
	}

	Layer::~Layer()
	{
		if (data)
		{
			for (int x = 0; x < width; x++)
			{
				free(data[x]);
			}
			free(data);
		}
	}

	void Layer::copy_into_data_from(const Layer& other)
	{
		data = (Tile **) calloc(other.width, sizeof(Tile *));
		for (int x = 0; x < other.width; x++)
		{
			data[x] = (Tile *) calloc(other.height, sizeof(Tile));
			for (int y = 0; y < other.height; y++)
			{
				data[x][y] = other.data[x][y];
			}
		}
	}

	bool Layer::IsFixedBottom()
	{
		if (name == "Ground" || name == "Ground overlay")
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Layer::Draw(SDL_Renderer * r, int x_offset, int y_offset, int start_y, int end_y)
	{
		for (int y = start_y; y < height; y++)
		{
			if (y >= end_y)
			{
				break;
			}
			for (int x = 0; x < width; x++)
			{
				Tile t = data[x][y];

				if (t.id == -1)
				{
					continue;
				}


				SDL_Texture * sheet_texture = t.sheet->GetTexture(r);
				SDL_Rect tile_rect = t.sheet->GetCoordinatesForTile(t.id);
				SDL_Rect dst_rect = { x_offset + (x * 32), y_offset + (y * 32), 32, 32 };
				SDL_RenderCopy(r, sheet_texture, &tile_rect, &dst_rect);
			}
		}
	}
}