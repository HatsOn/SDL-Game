#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleGameOver : public Module
{
public:
	ModuleGameOver(Application* app, bool start_enabled = true);
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	
	Animation gameover;
	Animation* current_animation;
};