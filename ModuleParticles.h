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

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE = COLLIDER_NONE, Uint32 delay = 0);

	void generateBomb(int power, Particle* p);
	void generateArm(int power, p2Point<int> particlePosition, p2Point<int> orientation);

	void addHorizontal(p2Point<int> orientation, int sizeExplosion, p2Point<int> particlePosition);
	void addVertical(p2Point<int> orientation, int sizeExplosion, p2Point<int> particlePosition);
	void addExplosionUp(p2Point<int> orientation, int sizeExplosion, p2Point<int> particlePosition);
	void addEvaporatingWall(p2Point<int> orientation, int sizeExplosion, p2Point<int> particlePosition);

	bool canExplode(p2Point<int> p, char orientation);
	bool canDestroy(p2Point<int> p, char orientation);

	void dropPowerUp(p2Point<int> particlePosition, int sizeX, int sizeY);

	void findParticle(COLLIDER_TYPE);


private:

	SDL_Texture* graphics;
	p2List<Particle*> active;

public:
	Particle speedpowerUp;
	Particle sizeExplosionPowerUp;
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

	Particle evaporatingWall;

	int bombLife;
	int explosionLife;
	int wallLife;
	bool spawned;
	p2Point<int> speedPowerUpLocation;
	p2Point<int> sizeExplosionPowerUpLocation;

};