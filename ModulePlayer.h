#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "bomb.h"


enum LookingLeftRight {					
	DIRECTIONLEFT = 0,
	DIRECTIONRIGHT = 1,
	NODIRECTIONSIDE = 2

};

enum LookingUpDown {
	DIRECTIONUP = 0,
	DIRECTIONDOWN= 1,
	NODIRECTIONVERTICAL = 2

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
	void leftRightCollision(LookingLeftRight direction);
	void upDownCollision(LookingUpDown direction);
	void UpdatePosition();
	p2Point<int> bombPos(p2Point<int> p);

public:

	bool hasCollided;


	//Effectes Sonors
	unsigned int caminar_fx;
	unsigned int bomba_fx;
	unsigned int powerup_fx;
	unsigned int mortpj_fx;
	unsigned int camina_fx;
	int audioChannel;

	int speedPowerUpCounter;
	int sizeBombPowerUpCounter;
	int numBombPowerUpCounter;

	

	p2Point<int> playerCollider;
	LookingLeftRight directionSide;
	LookingUpDown directionVertical;
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
	Animation dying;
	Animation ending;
	p2Point<int> positionTileMapUpperLeftCorner;
	p2Point<int> positionTileMapUpperRightCorner;
	p2Point<int> positionTileMapLowerLeftCorner;
	p2Point<int> positionTileMapLowerRightCorner;
	p2Point<int> positionTileMapMid;
	
	p2Point<int> lastPosition;
	p2Point<int> positionTileMap;
	p2Point<int> position;
	p2Point<int> bombPosition;
	bool bombOn;
	int bombPower;
	int numBombs;
	bool finished;
	int enemiesAlive;
	
	p2Point<int> speed;
	int speedValue;

	bool dead;

	bool canWalkUpperCorner;
	bool canWalkLowerCorner;





};