#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Particle
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);

	Particle* AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);
	void generateBomb(int power, Particle* p);
	bool canExplode(p2Point<int> p, char orientation);
	bool canDestroy(p2Point<int> p, char orientation);
	void dropPowerUp(p2Point<int> particlePosition, int sizeX, int sizeY);
	void findParticle(COLLIDER_TYPE);


private:

	SDL_Texture* graphics;
	p2List<Particle*> active;

public:

	unsigned int explosio_fx;

	Particle speedpowerUp;
	Particle sizeExplosionPowerUp;
	Particle bombNumberPowerUp;
	Particle bomb;
	Particle bombR;
	Particle explosion;
	Particle explosionUp;
	Particle explosionDown;
	Particle explosionLeft;
	Particle explosionRight;
	Particle horizontal;
	Particle vertical;
	Particle portal;
	Particle* portalBackup;

	Particle evaporatingWall;

	int bombLife;
	int explosionLife;
	int wallLife;
	bool spawned;
	p2Point<int> speedPowerUpLocation;
	p2Point<int> sizeExplosionPowerUpLocation;
	p2Point<int> bombNumberPowerUpLocation;

};