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

	SDL_Texture* introtitle;

	Animation zepelin;
	Animation balloonAnim;
	Animation zepelin3Anim;

	Animation* current_animation_zepelin1;
	Animation* current_animation_balloon;
	Animation* current_animation_zepelin2;

	unsigned int fx;
	int zepelinFPS;

	p2Point<int> positionZepelin;
	p2Point<int> positionBalloon;
	p2Point<int> positionZepelin3;

	p2Point<int> positiontitletop;
	p2Point<int> positiontitlebottom;

	unsigned int select_fx;
};