#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "bomb.h"


enum Looking {					
	Directiondown = 0,
	Directionright = 1,
	Directionleft = 2,
	Directionup = 3,
	DirectionupLeft = 4,
	DirectionupRight = 5,
	DirectiondownLeft = 6,
	DirectiondownRight = 7,
	NoDirection = 8

};


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void isWalkable();
	void OnCollision(Collider*, Collider*);

public:

	bool hasCollided;


	Looking direction;
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
	p2Point<int> positionTileMapUpperLeftCorner;
	p2Point<int> positionTileMapUpperRightCorner;
	p2Point<int> positionTileMapLowerLeftCorner;
	p2Point<int> positionTileMapLowerRightCorner;
	p2Point<int> positionTileMapMid;
	p2Point<int> speed;
	p2Point<int> lastPosition;
	p2Point<int> positionTileMap;
	p2Point<int> position;
	p2Point<int> bombPosition;
	bool bombOn;
};