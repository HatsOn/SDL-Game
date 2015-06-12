#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"


ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics2 = NULL;

	map.frames.PushBack({ 0, 0, 256, 272 });
	map.frames.PushBack({ 256, 0, 256, 272 });
	map.loop = true;
	map.speed = 0.05f;

}

ModuleMap::~ModuleMap()
{}

// Load assets
bool ModuleMap::Start()
{
	LOG("Loading Map assets");
	bool ret = true;

	//App->particles->findParticle(COLLIDER_FINISH);
	graphics2 = App->textures->Load("MapV1.1.png");

	App->audio->PlayMusic("Map.ogg", 0.5f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleMap::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics2);


	return true;
}

// Update: draw background
update_status ModuleMap::Update()
{
	current_animation = &map;
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->tileMap, 3.0f);
		App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
	}


	else if (App->input->GetKey(SDL_SCANCODE_B) == KEY_UP)

	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->tileBoss, 3.0f);
		App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
	}

	App->renderer->Blit(graphics2, 0, 0, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
