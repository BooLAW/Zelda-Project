#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1FileSystem.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Player.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;
	for(std::list<MapLayer*>::iterator item = data.layers.begin(); item != data.layers.end(); item++)
	{
		MapLayer* layer = (*item);

		if(layer->properties.Get("NoDraw") == 1)
			continue;

		for(int y = 0; y < data.height; ++y)
		{
			for(int x = 0; x < data.width; ++x)
			{
				int tile_id = layer->Get(x, y);
				if(tile_id > 0)
				{
					TileSet* tileset = GetTilesetFromTileId(tile_id);

					SDL_Rect r = tileset->GetTileRect(tile_id);
					iPoint pos = MapToWorld(x, y);

					App->render->Blit(tileset->texture, pos.x, pos.y, &r);
				}
			}
		}
	}
}

int Properties::Get(const char* value, int default_value) const
{
	for (std::list<Property*>::const_iterator item = list.begin(); item != list.end(); ++item)
	{
		if ((*item)->name == value)
			return (*item)->value;
	}
	return default_value;
}

TileSet* j1Map::GetTilesetFromTileId(int id) const
{
	std::list<TileSet*>::const_iterator item = data.tilesets.begin();
	TileSet* set = (*item);

	while(item != data.tilesets.end())
	{
		if(id < (*item)->firstgid)
		{
			set = *(--item);
			break;
		}
		set = (*item);
		item++;
	}

	return set;
}

iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if(data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * data.tile_width;
		ret.y = y * data.tile_height;
	}
	else if(data.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (data.tile_width * 0.5f);
		ret.y = (x + y) * (data.tile_height * 0.5f);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret(0,0);

	if(data.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / data.tile_width;
		ret.y = y / data.tile_height;
	}
	else if(data.type == MAPTYPE_ISOMETRIC)
	{
		
		float half_width = data.tile_width * 0.5f;
		float half_height = data.tile_height * 0.5f;
		ret.x = int( (x / half_width + y / half_height) / 2) - 1;
		ret.y = int( (y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

//TileData* TileSet::GetTileType(int tile_id)const
//{
//	
//}
// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// Remove all tilesets
	std::list<TileSet*>::iterator item;
	item = data.tilesets.begin();

	while(item != data.tilesets.end())
	{
		RELEASE((*item));
		item++;
	}
	data.tilesets.clear();

	// Remove all layers
	std::list<MapLayer*>::iterator item2;
	item2 = data.layers.begin();

	while(item2 != data.layers.end())
	{
		RELEASE((*item2));
		item2++;
	}
	data.layers.clear();

	// Clean up the pugui tree
	map_file.reset();

	return true;
}

int j1Map::TileCheck(int x, int y, Direction dir) const
{
	int ret = 0;
	//get the key navigation tiles(r)
	//Note: aqui el que fa es guardarse el numero del tileset en el que estan 2 
	//tiles clau de la navigation
	//el de no es pot passar i el detector de canvi d'escena
	int red_tile = data.tilesets.begin()._Ptr->_Next->_Myval->firstgid;//walkability tile to don't walk
																			 //int blue_tile = red_tile + 7;//walkability tile to get inside a building

	if (dir == Up)
	{
		iPoint ptemp = WorldToMap(x, y);
		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;
		int id_1 = (*item)->Get(ptemp.x, ptemp.y);

		if (id_1 == red_tile)
		{
			ret = 1;
		}
		/*	else if (id_1 == blue_tile)
		{
		App->scene->switch_map = 1;
		}*/
		else
			ret = 0;

	}
	if (dir == Left)
	{
		iPoint ptemp = WorldToMap(x, y);
		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;
		int id_1 = (*item)->Get(ptemp.x, ptemp.y);


		if (id_1 == red_tile)
		{
			ret = 1;
		}
		else
			ret = 0;
	}
	if (dir == Right)
	{
		iPoint ptemp = WorldToMap(x + 20, y);

		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;
		int id_1 = (*item)->Get(ptemp.x, ptemp.y);


		if (id_1 == red_tile)
		{
			ret = 1;
		}
		else
			ret = 0;
	}
	if (dir == Down)
	{
		iPoint ptemp = WorldToMap(x, y + 50);

		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;
		int id_1 = (*item)->Get(ptemp.x, ptemp.y);


		if (id_1 == red_tile)
		{
			ret = 1;
		}
		/*else if (id_1 == blue_tile)
		{
		App->scene->switch_map = 2;
		}*/
		else
			ret = 0;
	}
	if (dir == Down_L)
	{
		iPoint ptemp = WorldToMap(x, y + 50);

		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;

		int id_1 = (*item)->Get(ptemp.x, ptemp.y);


		if (id_1 == red_tile)
		{
			ret = 1;
		}
		/*else if (id_1 == blue_tile)
		{
		App->scene->switch_map = 2;
		}*/
		else
			ret = 0;
	}
	if (dir == Down_R)
	{
		iPoint ptemp = WorldToMap(x + 20, y + 50 );

		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;

		int id_1 = (*item)->Get(ptemp.x, ptemp.y);

		if (id_1 == red_tile)
		{
			ret = 1;
		}
		/*else if (id_1 == blue_tile)
		{
		App->scene->switch_map = 2;
		}*/
		else
			ret = 0;
	}
	if (dir == Up_R)
	{
		iPoint ptemp = WorldToMap(x + 20, y);

		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;
		int id_1 = (*item)->Get(ptemp.x, ptemp.y);

		if (id_1 == red_tile)
		{
			ret = 1;
		}
		/*else if (id_1 == blue_tile)
		{
		App->scene->switch_map = 2;
		}*/
		else
			ret = 0;
	}
	if (dir == Up_L)
	{
		iPoint ptemp = WorldToMap(x, y);

		std::list<MapLayer*>::const_iterator item = data.layers.end();
		item--;
		int id_1 = (*item)->Get(ptemp.x, ptemp.y);


		if (id_1 == red_tile)
		{
			ret = 1;
		}
		/*else if (id_1 == blue_tile)
		{
		App->scene->switch_map = 2;
		}*/
		else
			ret = 0;
	}

	//retornarem 0 si podem caminar o si es una blue tile
	return ret;
}
// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	char* buf;
	int size = App->fs->Load(tmp.GetString(), &buf);
	pugi::xml_parse_result result = map_file.load_buffer(buf, size);

	RELEASE(buf);

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	// Load general info ----------------------------------------------
	if(ret == true)
	{
		ret = LoadMap();
	}

	// Load all tilesets info ----------------------------------------------
	pugi::xml_node tileset;
	for(tileset = map_file.child("map").child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();

		if(ret == true)
		{
			ret = LoadTilesetDetails(tileset, set);
		}

		if(ret == true)
		{
			ret = LoadTilesetImage(tileset, set);
		}

		data.tilesets.push_back(set);
	}

	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for(layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if(ret == true)
			data.layers.push_back(lay);
	}

	if(ret == true)
	{
		LOG("Successfully parsed map XML file: %s", file_name);
		LOG("width: %d height: %d", data.width, data.height);
		LOG("tile_width: %d tile_height: %d", data.tile_width, data.tile_height);

		std::list<TileSet*>::iterator item = data.tilesets.begin();
		while(item != data.tilesets.end())
		{
			TileSet* s = (*item);
			LOG("Tileset ----");
			LOG("name: %s firstgid: %d", s->name.GetString(), s->firstgid);
			LOG("tile width: %d tile height: %d", s->tile_width, s->tile_height);
			LOG("spacing: %d margin: %d", s->spacing, s->margin);
			item++;
		}

		std::list<MapLayer*>::iterator item_layer = data.layers.begin();
		while(item_layer != data.layers.end())
		{
			MapLayer* l = (*item_layer);
			LOG("Layer ----");
			LOG("name: %s", l->name.GetString());
			LOG("tile width: %d tile height: %d", l->width, l->height);
			item_layer++;
		}
	}

	map_loaded = ret;

	return ret;
}

// Load map general properties
bool j1Map::LoadMap()
{
	bool ret = true;
	pugi::xml_node map = map_file.child("map");

	if(map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		data.width = map.attribute("width").as_int();
		data.height = map.attribute("height").as_int();
		data.tile_width = map.attribute("tilewidth").as_int();
		data.tile_height = map.attribute("tileheight").as_int();
		p2SString bg_color(map.attribute("backgroundcolor").as_string());

		data.background_color.r = 0;
		data.background_color.g = 0;
		data.background_color.b = 0;
		data.background_color.a = 0;

		if(bg_color.Length() > 0)
		{
			p2SString red, green, blue;
			bg_color.SubString(1, 2, red);
			bg_color.SubString(3, 4, green);
			bg_color.SubString(5, 6, blue);

			int v = 0;

			sscanf_s(red.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.r = v;

			sscanf_s(green.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.g = v;

			sscanf_s(blue.GetString(), "%x", &v);
			if(v >= 0 && v <= 255) data.background_color.b = v;
		}

		p2SString orientation(map.attribute("orientation").as_string());

		if(orientation == "orthogonal")
		{
			data.type = MAPTYPE_ORTHOGONAL;
		}
		else if(orientation == "isometric")
		{
			data.type = MAPTYPE_ISOMETRIC;
		}
		else if(orientation == "staggered")
		{
			data.type = MAPTYPE_STAGGERED;
		}
		else
		{
			data.type = MAPTYPE_UNKNOWN;
		}
	}

	return ret;
}

bool j1Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	set->name.create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tile_width = tileset_node.attribute("tilewidth").as_int();
	set->tile_height = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	pugi::xml_node offset = tileset_node.child("tileoffset");

	if(offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}

	return ret;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if(image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if(set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if(set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / set->tile_width;
		set->num_tiles_height = set->tex_height / set->tile_height;
	}

	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	LoadProperties(node, layer->properties);
	pugi::xml_node layer_data = node.child("data");

	if(layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width*layer->height];
		memset(layer->data, 0, layer->width*layer->height);

		int i = 0;
		for(pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			layer->data[i++] = tile.attribute("gid").as_int(0);
		}
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool j1Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	pugi::xml_node data = node.child("properties");

	if(data != NULL)
	{
		pugi::xml_node prop;

		for(prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.list.push_back(p);
		}
	}

	return ret;
}


bool j1Map::CreateWalkabilityMap(int& width, int& height, uchar** buffer) const
{
	bool ret = false;
	std::list<MapLayer*>::const_iterator item;
	//iterate each layer
	for (item = data.layers.begin(); item != data.layers.end(); item++)
	{
		MapLayer* layer = (*item);

		if (layer->properties.Get("Navigation", 0) == 0)
			continue;

		uchar* map = new uchar[layer->width*layer->height];
		memset(map, 1, layer->width*layer->height);

		for(int y = 0; y < data.height; ++y)
		{
			for(int x = 0; x < data.width; ++x)
			{
				int i = (y*layer->width) + x;

				int tile_id = layer->Get(x, y);
				//ensure that the tile_id are correct(>0)
				
				if (tile_id == 10)
					map[i] = 1;

				TileSet* tileset = (tile_id > 0) ? GetTilesetFromTileId(tile_id) : NULL;
				
				if(tileset != NULL)
				{
					//map[i] = (tile_id - tileset->firstgid) > 0 ? 0 : 1;

				}
			}
		}

		*buffer = map;
		width = data.width;
		height = data.height;
		ret = true;

		break;
	}
	return ret;
}