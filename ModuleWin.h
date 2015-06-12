#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleWin : public Module
{
public:
	ModuleWin(Application* app, bool start_enabled = true);
	~ModuleWin();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;

	Animation win;
	Animation* current_animation;
};