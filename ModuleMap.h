#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleMap : public Module
{
public:
	ModuleMap(Application* app, bool start_enabled = true);
	~ModuleMap();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics2;

	Animation map;
	Animation* current_animation;

	unsigned int fx;
	unsigned int counter;
};