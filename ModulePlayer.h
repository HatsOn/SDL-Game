#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "bomb.h"
class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void isWalkable();

public:

	SDL_Texture* graphics;
	SDL_Texture* bombs;
	p2DynArray<bomb>* bomblist;
	Collider* collider;
	Animation* current_animation;
	Animation* bombAnimation;
	Animation idle;
	Animation up;
	Animation left;
	Animation right;
	Animation down;
	Animation bomb;
	p2Point<int> position;
	p2Point<int> bombPosition;
	bool bombOn;
};