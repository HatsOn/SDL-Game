#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "bomb.h"

class ModuleBoss :
	public Module
{

public:

	SDL_Texture* graphics;
	Collider* bossCollider;
	Collider* mazeCollider;
	Animation* current_animation;
	Animation idle;
	Animation smashing;
	

	p2Point<int> speed;
	p2Point<int> position;
	


	ModuleBoss(Application* app, bool start_enabled = true);

	~ModuleBoss();

	bool Start();
	bool CleanUp();
	update_status Update();


	void changeBossPosition(p2Point<int> position);
};

