#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1FileSystem.h"
#include "j1Fonts.h"

#include "SDL\include\SDL.h"
#include "SDL_TTF\include\SDL_ttf.h"
#pragma comment( lib, "SDL_ttf/libx86/SDL2_ttf.lib" )

j1Fonts::j1Fonts() : j1Module()
{
	name.create("fonts");
}

// Destructor
j1Fonts::~j1Fonts()
{}

// Called before render is available
bool j1Fonts::Awake(pugi::xml_node& conf)
{
	LOG("Init True Type Font library");
	bool ret = true;

	if(TTF_Init() == -1)
	{
		LOG("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		ret = false;
	}
	else
	{
		const char* path = conf.child("default_font").attribute("file").as_string(DEFAULT_FONT);
		title = Load(path, conf.child("title_font").attribute("size").as_int(DEFAULT_TITLE_SIZE));
		default = Load(path, conf.child("default_font").attribute("size").as_int(DEFAULT_FONT_SIZE));
	}

	return ret;
}

// Called before quitting
bool j1Fonts::CleanUp()
{
	LOG("Freeing True Type fonts and library");
	for(std::list<TTF_Font*>::iterator item = fonts.begin(); item != fonts.end(); item++)
	{
		TTF_CloseFont((*item));
	}

	fonts.clear();
	TTF_Quit();
	return true;
}

// Load new texture from file path
TTF_Font* const j1Fonts::Load(const char* path, int size)
{
	TTF_Font* font = TTF_OpenFontRW(App->fs->Load(path), 1, size);

	if(font == NULL)
	{
		LOG("Could not load TTF font with path: %s. TTF_OpenFont: %s", path, TTF_GetError());
	}
	else
	{
		LOG("Successfully loaded font %s size %d", path, size);
		fonts.push_back(font);
	}
	return font;
}

// Print text using font
SDL_Texture* j1Fonts::Print(const char* text, TTF_Font* font, int& width, int& height, SDL_Color color)
{
	SDL_Texture* ret = NULL;
	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped((font) ? font : default, text, color, 300);

	if(surface == NULL)
	{
		LOG("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		width = surface->w;
		height = surface->h;
		ret = App->tex->LoadSurface(surface);
		SDL_FreeSurface(surface);
	}

	return ret;
}
