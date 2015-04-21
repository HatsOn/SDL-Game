#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("BombermanTiles.png");

	// Bomb particle

	bomb.anim.frames.PushBack({ 509, 185, 16, 16});
	bomb.anim.frames.PushBack({ 526, 185, 16, 16 });
	bomb.anim.frames.PushBack({ 543, 185, 16, 16 });
	bomb.life = 3000;
	bomb.anim.speed = 10.05f;
	bomb.anim.loop = true;

	// Explosion particle
	
	explosion.anim.frames.PushBack({475, 134, 16, 16});
	explosion.anim.frames.PushBack({492, 134, 16, 16});
	explosion.anim.frames.PushBack({509, 134, 16, 16});
	explosion.anim.frames.PushBack({527, 134, 16, 16});
	
	explosion.anim.loop = false;
	




	explosionUp.anim.frames.PushBack({ 475, 134, 16, 16 });
	explosionUp.anim.frames.PushBack({ 492, 134, 16, 16 });
	explosionUp.anim.frames.PushBack({ 509, 134, 16, 16 });
	explosionUp.anim.frames.PushBack({ 527, 134, 16, 16 });

	explosionUp.anim.loop = false;
	




	explosionDown.anim.frames.PushBack({ 475, 134, 16, 16 });
	explosionDown.anim.frames.PushBack({ 492, 134, 16, 16 });
	explosionDown.anim.frames.PushBack({ 509, 134, 16, 16 });
	explosionDown.anim.frames.PushBack({ 527, 134, 16, 16 });

	explosionDown.anim.loop = false;
	

	explosionLeft.anim.frames.PushBack({ 475, 134, 16, 16 });
	explosionLeft.anim.frames.PushBack({ 492, 134, 16, 16 });
	explosionLeft.anim.frames.PushBack({ 509, 134, 16, 16 });
	explosionLeft.anim.frames.PushBack({ 527, 134, 16, 16 });

	explosionLeft.anim.loop = false;
	


	explosionRight.anim.frames.PushBack({ 475, 134, 16, 16 });
	explosionRight.anim.frames.PushBack({ 492, 134, 16, 16 });
	explosionRight.anim.frames.PushBack({ 509, 134, 16, 16 });
	explosionRight.anim.frames.PushBack({ 527, 134, 16, 16 });

	explosionRight.anim.loop = false;
	

	



	// Laser particle
	/*
	laser.anim.frames.PushBack({200, 120, 32, 12});
	laser.anim.frames.PushBack({230, 120, 32, 12});
	laser.speed.x = 7;
	laser.life = 1000;
	laser.anim.speed = 0.05f;
	*/
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
			/*if (p->collider->type == COLLIDER_PLAYER_SHOT)
			{
				App->particles->AddParticle(App->particles->explosion, p->position.x - 16, p->position.y - 16, COLLIDER_PLAYER_EXPLOSION);
			}*/
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
		if(tmp->data->collider == c1 )
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