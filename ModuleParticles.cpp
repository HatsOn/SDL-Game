#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"
#include <time.h>

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{

	srand(time(NULL));

	LOG("Loading particles");
	graphics = App->textures->Load("BombermanTiles.png");

	bombLife = 2000;
	explosionLife = 2000;
	// Bomb particle

	bomb.anim.frames.PushBack({ 356, 151, 16, 16 });
	bomb.anim.frames.PushBack({ 373, 151, 16, 16 });
	bomb.anim.frames.PushBack({ 390, 151, 16, 16 });
	bomb.anim.frames.PushBack({ 373, 151, 16, 16 });
	bomb.life = bombLife;
	bomb.anim.speed = 0.05f;

	bombR.anim.frames.PushBack({ 255, 83, 16, 16 });
	bombR.anim.frames.PushBack({ 271, 83, 16, 16 });
	bombR.anim.frames.PushBack({ 288, 83, 16, 16 });
	bombR.anim.frames.PushBack({ 271, 83, 16, 16 });
	bombR.life = bombLife*1.5;
	bombR.anim.speed = 0.05f;
		

	evaporatingWall.anim.frames.PushBack({ 254, 151, 16, 16 });
	evaporatingWall.anim.frames.PushBack({ 271, 151, 16, 16 });
	evaporatingWall.anim.frames.PushBack({ 288, 151, 16, 16 });
	evaporatingWall.anim.frames.PushBack({ 305, 151, 16, 16 });
	evaporatingWall.anim.frames.PushBack({ 322, 151, 16, 16 });
	evaporatingWall.anim.frames.PushBack({ 339, 151, 16, 16 });
	evaporatingWall.life = bombLife*1.5;
	evaporatingWall.anim.speed = 0.05f;
	evaporatingWall.anim.loop = false;

	




	// Explosion particle
	
	explosion.anim.frames.PushBack({322, 100, 16, 16});
	explosion.anim.frames.PushBack({ 339, 100, 16, 16 });
	explosion.anim.frames.PushBack({ 356, 100, 16, 16 });
	explosion.anim.frames.PushBack({ 373, 100, 16, 16 });
	explosion.anim.frames.PushBack({ 322, 117, 16, 16 });
	explosion.anim.speed = 0.05f;
	explosion.life = explosionLife;
	explosion.anim.loop = false;
	




	explosionUp.anim.frames.PushBack({ 372, 66, 16, 16 });
	explosionUp.anim.frames.PushBack({ 372, 82, 16, 16 });
	explosionUp.anim.frames.PushBack({ 356, 82, 16, 16 });
	explosionUp.anim.frames.PushBack({ 339, 82, 16, 16 });
	explosionUp.anim.frames.PushBack({ 322, 82, 16, 16 });
	explosionUp.life = explosionLife;
	explosionUp.anim.speed = 0.05f;
	explosionUp.anim.loop = false;
	




	explosionDown.anim.frames.PushBack({ 339, 134, 16, 16 });
	explosionDown.anim.frames.PushBack({ 356, 134, 16, 16 });
	explosionDown.anim.frames.PushBack({ 373, 134, 16, 16 });
	explosionDown.anim.frames.PushBack({ 322, 134, 16, 16 });
	explosionDown.anim.frames.PushBack({ 305, 83, 16, 16 });
	explosionDown.life = explosionLife;
	explosionDown.anim.speed = 0.05f;
	explosionDown.anim.loop = false;
	

	explosionLeft.anim.frames.PushBack({ 322, 66, 16, 16 });
	explosionLeft.anim.frames.PushBack({ 305, 66, 16, 16 });
	explosionLeft.anim.frames.PushBack({ 288, 66, 16, 16 });
	explosionLeft.anim.frames.PushBack({ 271, 66, 16, 16 });
	explosionLeft.anim.frames.PushBack({ 254, 66, 16, 16 });
	explosionLeft.life = explosionLife;
	explosionLeft.anim.speed = 0.05f;
	explosionLeft.anim.loop = false;
	


	explosionRight.anim.frames.PushBack({ 271, 100, 16, 16 });
	explosionRight.anim.frames.PushBack({ 271, 117, 16, 16 });
	explosionRight.anim.frames.PushBack({ 271, 134, 16, 16 });
	explosionRight.anim.frames.PushBack({ 305, 100, 16, 16 });
	explosionRight.anim.frames.PushBack({ 305, 117, 16, 16 });
	explosionRight.life = explosionLife;
	explosionRight.anim.speed = 0.05f;
	explosionRight.anim.loop = false;
	

	horizontal.anim.frames.PushBack({ 254, 100, 16, 16 });
	horizontal.anim.frames.PushBack({ 254, 117, 16, 16 });
	horizontal.anim.frames.PushBack({ 254, 134, 16, 16 });
	horizontal.anim.frames.PushBack({ 288, 100, 16, 16 });
	horizontal.anim.frames.PushBack({ 288, 117, 16, 16 });
	horizontal.life = explosionLife;
	horizontal.anim.speed = 0.05f;
	horizontal.anim.loop = false;


	vertical.anim.frames.PushBack({ 339, 117, 16, 16 });
	vertical.anim.frames.PushBack({ 356, 117, 16, 16 });
	vertical.anim.frames.PushBack({ 373, 117, 16, 16 });
	vertical.anim.frames.PushBack({ 288, 134, 16, 16 });
	vertical.anim.frames.PushBack({ 305, 134, 16, 16 });
	vertical.life = explosionLife;
	vertical.anim.speed = 0.05f;
	vertical.anim.loop = false;


	speedpowerUp.anim.frames.PushBack({ 233, 98, 16, 16 });
	speedpowerUp.anim.frames.PushBack({ 233, 114, 16, 16 });
	speedpowerUp.life = 10000;
	speedpowerUp.anim.speed = 0.05f;
	speedpowerUp.anim.loop = true;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	p2List_item<Particle*>* tmp = active.getFirst();
	p2List_item<Particle*>* tmp_next = active.getFirst();

	while(tmp != NULL)
	{
		Particle* p = tmp->data;
		tmp_next = tmp->next;

		if(p->Update() == false)
		{
			if (p->collider->type == COLLIDER_PLAYER_SHOT)
			{
				///////////////
				generateBomb(App->player->bombPower, p);
			}


			delete p;
			active.del(tmp);
		}		
		else if(SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
				App->audio->PlayFx(p->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}

// Always destroy particles that collide
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	// TODO 5: Fer que cada vegada que un laser collisini sorti una explosio
  	p2List_item<Particle*>* tmp = active.getFirst();

	while(tmp != NULL)
	{
		/*
		if(tmp->data->collider == c1 )
		{	
			delete tmp->data;
			active.del(tmp);
			break;
		}
		*/
		if (c2->type == COLLIDER_PLAYER)
		{
			delete tmp->data;
			active.del(tmp);
			break;
		}



		tmp = tmp->next;
	}
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	if(collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({p->position.x, p->position.y, 0, 0}, collider_type, this);
	}

	active.add(p);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

Particle::~Particle()
{
	if(collider)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = {position.x, position.y, r.w, r.h};
	}

	return ret;
}


void ModuleParticles::generateBomb(int power, Particle* p)
{
	bool upHand = false;
	bool downHand = false;
	bool leftHand = false;
	bool rightHand = false;

	int size = 16;
	int i = 0;
	// En principi aixo ho he posat per a tenir sempre la posicio de la particula actual
	p2Point<int> particlePosition = p->position;


	//Center
	AddParticle(explosion, p->position.x, p->position.y, COLLIDER_PLAYER_EXPLOSION);
	power = 5;
	//Arms
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	particlePosition = p->position;
	for (i = 1; i < power; i++)
	{
		if (canExplode(particlePosition, 'n'))
		{
			AddParticle(vertical,
				p->position.x,
				p->position.y - size*i,
				COLLIDER_PLAYER_EXPLOSION);
			particlePosition.y -= 16;
		}
		else
		{
			if (canDestroy(particlePosition, 'n')) // Si es destruible
			{
				App->tileMap->map.tile[(particlePosition.x + 8) / TILE_SIZE][(particlePosition.y - 8) / TILE_SIZE - SCOREOFFSET] = 19;
				AddParticle(evaporatingWall,
					p->position.x,
					p->position.y - size*i,
					COLLIDER_PLAYER_EXPLOSION);
			}
			upHand = true;
			break;
		}
	}
	if (!upHand && canExplode(particlePosition, 'n'))
		AddParticle(explosionUp, p->position.x, p->position.y - size*i, COLLIDER_PLAYER_EXPLOSION);
	else if (canDestroy(particlePosition, 'n'))
	{
		App->tileMap->map.tile[(particlePosition.x + 8) / TILE_SIZE][(particlePosition.y - 8) / TILE_SIZE - SCOREOFFSET] = 19;
		AddParticle(evaporatingWall,
			p->position.x,
			p->position.y - size*i,
			COLLIDER_PLAYER_EXPLOSION);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	particlePosition = p->position;
	for (i = 1; i < power; i++)
	{
		if (canExplode(particlePosition, 's'))
		{
			AddParticle(vertical,
				p->position.x,
				p->position.y + size*i,
				COLLIDER_PLAYER_EXPLOSION);
			particlePosition.y += 16;
		}
		else
		{
			if (canDestroy(particlePosition, 's')) // Si es destruible
			{
				App->tileMap->map.tile[(particlePosition.x + 8) / TILE_SIZE][(particlePosition.y + 16 + 8) / TILE_SIZE - SCOREOFFSET] = 19;
				AddParticle(evaporatingWall,
					p->position.x,
					p->position.y + size*i,
					COLLIDER_PLAYER_EXPLOSION);
			}
			downHand = true;
			break;
		}
	}
	if (!downHand && canExplode(particlePosition, 's'))
		AddParticle(explosionDown, p->position.x, p->position.y + size*i, COLLIDER_PLAYER_EXPLOSION);
	else if (canDestroy(particlePosition, 's'))
	{
		App->tileMap->map.tile[(particlePosition.x + 8) / TILE_SIZE][(particlePosition.y + 16 + 8) / TILE_SIZE - SCOREOFFSET] = 19;
		AddParticle(evaporatingWall,
			p->position.x,
			p->position.y + size*i,
			COLLIDER_PLAYER_EXPLOSION);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	particlePosition = p->position;
	for (i = 1; i < power; i++)
	{
		if (canExplode(particlePosition, 'o'))
		{
			AddParticle(horizontal,
				p->position.x - size*i,
				p->position.y,
				COLLIDER_PLAYER_EXPLOSION);
			particlePosition.x -= 16;
		}
		else
		{
			if (canDestroy(particlePosition, 'o')) // Si es destruible
			{
				App->tileMap->map.tile[(particlePosition.x - 8) / TILE_SIZE][(particlePosition.y + 8) / TILE_SIZE - SCOREOFFSET] = 19;
				AddParticle(evaporatingWall,
					p->position.x - size*i,
					p->position.y,
					COLLIDER_PLAYER_EXPLOSION);
			}

			leftHand = true;
			break;
		}
	}
	if (!leftHand && canExplode(particlePosition, 'o'))
		AddParticle(explosionLeft, p->position.x - size*i, p->position.y, COLLIDER_PLAYER_EXPLOSION);
	else if (canDestroy(particlePosition, 'o'))
	{
		App->tileMap->map.tile[(particlePosition.x - 8) / TILE_SIZE][(particlePosition.y + 8) / TILE_SIZE - SCOREOFFSET] = 19;
		AddParticle(evaporatingWall,
			p->position.x - size*i,
			p->position.y,
			COLLIDER_PLAYER_EXPLOSION);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	particlePosition = p->position;
	for (i = 1; i < power; i++)
	{
		if (canExplode(particlePosition, 'e'))
		{
			AddParticle(horizontal,
				p->position.x + size*i,
				p->position.y,
				COLLIDER_PLAYER_EXPLOSION);
			particlePosition.x += 16;
		}
		else
		{
			if (canDestroy(particlePosition, 'e')) // Si es destruible
			{
				App->tileMap->map.tile[(particlePosition.x + 8 + 16) / TILE_SIZE][(particlePosition.y + 8) / TILE_SIZE - SCOREOFFSET] = 19;
				if ((rand() % 100 + 1) <= 25)
				{
					App->tileMap->isSpeedPowerUp = true;
					//(rand()% 100 + 1) <= 25
					if (true)
					{
						speedPowerUpLocation.x = (particlePosition.x + 16);

						speedPowerUpLocation.y = (particlePosition.y);


						AddParticle(speedpowerUp, speedPowerUpLocation.x, speedPowerUpLocation.y, COLLIDER_SPEEDPOWERUP);
					}					
				}
				AddParticle(evaporatingWall,
					p->position.x + size*i,
					p->position.y,
					COLLIDER_PLAYER_EXPLOSION);
				rightHand = true;
				break;
			}
		}
	}
	if (!rightHand && canExplode(particlePosition, 'e'))
		AddParticle(explosionRight, p->position.x + size*i, p->position.y, COLLIDER_PLAYER_EXPLOSION);
	else if (canDestroy(particlePosition, 'e'))
	{
		App->tileMap->map.tile[(particlePosition.x + 8 + 16) / TILE_SIZE][(particlePosition.y + 8) / TILE_SIZE - SCOREOFFSET] = 19;
		AddParticle(evaporatingWall,
			p->position.x + size*i,
			p->position.y,
			COLLIDER_PLAYER_EXPLOSION);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
}

bool ModuleParticles::canExplode(p2Point<int> p, char orientation)
{
	switch (orientation)
	{
	case 'n':
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(p.x + 8) / TILE_SIZE][(p.y - 8) / TILE_SIZE - SCOREOFFSET]))
		{
			return false;
		}
		break;
	case 's':
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(p.x + 8) / TILE_SIZE][(p.y + 8 + 16) / TILE_SIZE - SCOREOFFSET]))

		{
			return false;
		}
		break;
	case 'o':
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(p.x - 8) / TILE_SIZE][(p.y + 8) / TILE_SIZE - SCOREOFFSET]))
		{
			return false;
		}
		break;
	case 'e':
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(p.x + 16 +8) / TILE_SIZE][(p.y + 8) / TILE_SIZE - SCOREOFFSET]))
		{
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}

bool ModuleParticles::canDestroy(p2Point<int> p, char orientation)
{
	switch (orientation)
	{
	case 'n':
				
		if (App->tileMap->map.tile[(p.x + 8) / TILE_SIZE][(p.y - 8) / TILE_SIZE - SCOREOFFSET] == 12 
			|| App->tileMap->map.tile[(p.x + 8) / TILE_SIZE][(p.y - 8) / TILE_SIZE - SCOREOFFSET] == 4)
		{
			return true;
		}
		break;
	case 's':
		
		if (App->tileMap->map.tile[(p.x + 8) / TILE_SIZE][(p.y + 16 + 8) / TILE_SIZE - SCOREOFFSET] == 12
			|| App->tileMap->map.tile[(p.x + 8) / TILE_SIZE][(p.y +16+ 8) / TILE_SIZE - SCOREOFFSET] == 4)
		{
			return true;
		}
		break;
	case 'o':
		if (App->tileMap->map.tile[(p.x - 8) / TILE_SIZE][(p.y + 8) / TILE_SIZE - SCOREOFFSET] == 12
			|| App->tileMap->map.tile[(p.x - 8) / TILE_SIZE][(p.y + 8) / TILE_SIZE - SCOREOFFSET] == 4)
		{
			return true;
		}
		break;
	case 'e':
		if (App->tileMap->map.tile[(p.x + 16 + 8) / TILE_SIZE][(p.y + 8) / TILE_SIZE - SCOREOFFSET] == 12
			|| App->tileMap->map.tile[(p.x + 16 + 8) / TILE_SIZE][(p.y + 8) / TILE_SIZE - SCOREOFFSET] == 4)
		{
			return true;
		}
		break;
	default:
		break;
	}
	return false;
}