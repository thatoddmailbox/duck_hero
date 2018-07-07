#include "level.hpp"

namespace duckhero
{
	Level::Level()
	{

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

				if (sheet == nullptr)
				{
					Log::Warning("Level::LoadFromFile", "couldn't find spritesheet for tileset!");
					continue;
				}

				spritesheets[firstgid] = sheet;
			}

			// start reading the layers
			for (pugi::xml_node layerNode : map.children("layer"))
			{
				const char * name = layerNode.attribute("name").value();

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
				pugi::xml_node data = layerNode.child("data");
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
		}
		else
		{
			Log::Warning("Level::LoadFromFile", "invalid XML file!");
			returnValue = false;
		}

		free(buffer);

		return returnValue;
	}

	void Level::Draw(SDL_Renderer * r, int x_offset, int y_offset)
	{
		for (Layer& layer : layers)
		{
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					Tile t = layer.data[x][y];

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

	Layer::Layer()
	{
		name = "";
		width = 0;
		height = 0;
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
}