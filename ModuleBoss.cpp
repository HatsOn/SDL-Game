#include "Globals.h"
#include "Application.h"
#include "ModuleBoss.h"

ModuleBoss::ModuleBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;
	speed.x = 1;
	speed.y = 1;


	// idle animation (just the bomberman
	idle.frames.PushBack({ 525, 248, 601 - 525, 399 - 248 }); //525,248 10,35
	// move upwards
	smashing.frames.PushBack({ 525, 248, 601 - 525, 399 - 248 });
	smashing.frames.PushBack({ 606, 248, 682 - 606, 399 - 248 });
	smashing.frames.PushBack({ 687, 248, 763 - 687, 399 - 248 });
	smashing.frames.PushBack({ 768, 248, 844 - 768, 399 - 248 });
	smashing.loop = true;
	smashing.speed = 0.05f;


	current_animation = &idle;

}


ModuleBoss::~ModuleBoss()
{
}



bool ModuleBoss::Start()
{
	App->particles->Enable();
	App->collision->Enable();

	LOG("Loading BOSS");

	//caminar_fx = App->audio->LoadFx("caminar.ogg");

	graphics = App->textures->Load("BombermanTiles.png");

	speed.x = 0;
	speed.y = 0;
	position.x = 96-16 ;
	position.y = 64 + 16 + SCOREOFFSET;

	bossCollider = App->collision->AddCollider({ (position.x), (position.y), 55, 63 }, COLLIDER_BOSS, this);

	return true;
}

bool ModuleBoss::CleanUp()
{
	LOG("Unloading player");
	//delete collider;

	return true;
}

update_status ModuleBoss::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_REPEAT)
	{
		position.y -= 1;
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_REPEAT)
	{
		position.y += 1;
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT)
	{
		position.x -= 1;
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT)
	{
		position.x += 1;
	}

	/*if (App->player->position.x != position.x)
	{
		position.x +=  -1 * (App->player->position.x / App->player->position.x);
	}*/


	//position.y += 1;
	bossCollider->SetPos(position.x+10, position.y+35);
	current_animation = &idle;






	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	

	return UPDATE_CONTINUE;
}

void ModuleBoss::changeBossPosition(p2Point<int> _position)
{
	position = _position;
	bossCollider->SetPos(_position.x, _position.y);
}
