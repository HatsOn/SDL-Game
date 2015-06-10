#pragma once

#include "Module.h"
//#include "SDL/include/SDL.h"
struct enemy
{
	p2Point<int> position;
	Collider* collider;
	p2Point<int> speed;
	LookingLeftRight directionSide;
	LookingUpDown directionVertical;
	int n;
};

/*enum LookingLeftRight {
	DIRECTIONLEFT = 0,
	DIRECTIONRIGHT = 1,
	NODIRECTIONSIDE = 2

};

enum LookingUpDown {
	DIRECTIONUP = 0,
	DIRECTIONDOWN = 1,
	NODIRECTIONVERTICAL = 2

};
*/

class ModuleTileMap : public Module
{
private:

public:
	Map map;
	p2Point<int> speedPowerUpLocation;
	
	int deathCount;
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



	SDL_Rect tile29;
	SDL_Rect tile30;
	SDL_Rect tile31;
	SDL_Rect tile32;
	// --- 2
	SDL_Rect tile33;
	SDL_Rect tile34;
	SDL_Rect tile35;
	SDL_Rect tile36;
	// --- 3
	SDL_Rect tile37;
	SDL_Rect tile38;
	SDL_Rect tile39;
	SDL_Rect tile40;
	// --- 4
	SDL_Rect tile41;
	SDL_Rect tile42;
	SDL_Rect tile43;
	SDL_Rect tile44;
	// --- 5
	SDL_Rect tile45;

	SDL_Rect tile46;

	SDL_Rect portal;
	SDL_Rect rEnemy1;
	SDL_Rect score;

	//Enemy
	p2DynArray<enemy> enemies;
	enemy enemy1;
	enemy enemy2;
	enemy enemy3;

	enemy changeDirection;
	
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
	void OnCollision(Collider* c1, Collider* c2);
	void PrintMap()const;
	void paintEnemies();
	void moveEnemy();
	void enemyMovement();
	void leftRightCollision(enemy*, LookingLeftRight&);
	void UpDownCollision(enemy*, LookingUpDown&);


};

