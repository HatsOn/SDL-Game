#pragma once

#include "Module.h"
//#include "SDL/include/SDL.h"
struct enemy
{
	p2Point<int> position;
	Collider* collider;
};

class ModuleTileMap : public Module
{
private:

public:
	Map map;
	p2Point<int> speedPowerUpLocation;
	

	SDL_Texture* tilesReference;
	SDL_Texture* bomblvl1;
	SDL_Texture* portalImg;
	SDL_Texture* enemyImg;
	SDL_Texture* scoreImg;
	
	p2DynArray<int> nonWalkableTiles;

	SDL_Rect tile1;
	SDL_Rect tile2;
	SDL_Rect tile3;
	SDL_Rect tile4;
	SDL_Rect tile5;
	SDL_Rect tile6;
	SDL_Rect tile7;
	SDL_Rect tile8;
	SDL_Rect tile9;
	SDL_Rect tile10;
	SDL_Rect tile11;
	SDL_Rect tile12;
	SDL_Rect tile13;
	SDL_Rect tile14;
	SDL_Rect tile15;
	SDL_Rect tile16;
	SDL_Rect tile17;
	SDL_Rect tile18;
	SDL_Rect tile19;
	SDL_Rect tile20;
	SDL_Rect tile21;
	SDL_Rect tile22;

	SDL_Rect tile23;
	SDL_Rect tile24;
	SDL_Rect tile25;
	SDL_Rect tile26;
	SDL_Rect tile27;
	SDL_Rect tile28;


	SDL_Rect portal;
	SDL_Rect rEnemy1;
	SDL_Rect score;

	//Enemy
	p2DynArray<enemy> enemies;
	enemy enemy1;
	enemy enemy2;
	enemy enemy3;
	
	bool isSpeedPowerUp;
	bool isExplosionSizePowerUp;
	
public:

	ModuleTileMap(Application* app, bool start_enabled);

	// Destructor
	virtual ~ModuleTileMap()
	{
		
	}

	bool Start();

	update_status Update();

	void prepareTiles();


	void BuildMap();
	void CollisionMap();
	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	void LoadMap(char*);

	void PrintMap()const;
	void paintEnemies();
	void moveEnemy();
	void enemyMovement();
};

