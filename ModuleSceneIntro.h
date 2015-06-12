#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Texture* zepelin3;
	SDL_Texture* balloon;
	SDL_Texture* zepelin2;

	SDL_Texture* titletop;
	SDL_Texture* titlebottom;

	p2Point<int> speed;
	p2Point<int> position;

	Animation zepelin;
	Animation* current_animation;

	unsigned int fx;
	p2Point<int> positionZepelin;

	unsigned int select_fx;
};