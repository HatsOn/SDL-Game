#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "bomb.h"

enum bossState
{
	TOP,
	DOWN,
	LEFT,
	RIGHT,
	CENTERED
};


class ModuleBoss :
	public Module
{

public:

	bossState state;

	SDL_Texture* graphics;
	Collider* bossCollider;
	Collider* mazeCollider;
	Animation* current_animation;
	Animation idle;
	Animation smashing;
	Animation damage;
	
	

	p2Point<int> speed;
	p2Point<int> position;
	int framesMove;
	int mazeCounter;

	ModuleBoss(Application* app, bool start_enabled = true);

	~ModuleBoss();

	bool Start();
	bool CleanUp();
	update_status Update();


	void changeBossPosition(p2Point<int> position);
	void changeBossPosition(int x, int y);
	void changeMovementState(bossState _state);
	bool playerInDangerZone();
};

