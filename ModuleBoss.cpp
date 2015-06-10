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
	idle.frames.PushBack({ 515, 213, 77, 100 }); //525,248 10,35
	// move upwards
	smashing.frames.PushBack({ 515, 213, 77, 100 });
	smashing.frames.PushBack({ 596, 213, 56, 100 });
	smashing.frames.PushBack({ 658, 213, 56, 100 });
	smashing.frames.PushBack({ 719, 249, 58, 116 });
	smashing.loop = true;
	smashing.speed = 0.01f;


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
	position.x = 100;
	position.y = 100;

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

	if (App->player->position.x != position.x)
	{
		position.x +=  -1 * (App->player->position.x / App->player->position.x);
	}


	//position.y += 1;
	bossCollider->SetPos(position.x+10, position.y+35);


	current_animation = &smashing;
	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	

	return UPDATE_CONTINUE;
}
