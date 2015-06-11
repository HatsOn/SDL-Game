#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"


ModuleMap::ModuleMap(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics2 = NULL;
	fx = 0;
}

ModuleMap::~ModuleMap()
{}

// Load assets
bool ModuleMap::Start()
{
	LOG("Loading Map assets");
	bool ret = true;

	//App->particles->findParticle(COLLIDER_FINISH);
	graphics2 = App->textures->Load("MapV1.png");
	graphics3 = App->textures->Load("MapV2.png");
	App->audio->PlayMusic("Map.ogg", 0.5f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleMap::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics2);
	App->textures->Unload(graphics3);

	return true;
}

// Update: draw background
update_status ModuleMap::Update()
{
	App->renderer->Blit(graphics2, 0, 0, NULL);
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->tileMap, 3.0f);
		App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_UP)
	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->map, 3.0f);
		App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
	}
	return UPDATE_CONTINUE;
}

/*
if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
{
//App->tileMap->Enable();
App->fade->FadeToBlack(this, App->tileMap, 3.0f);
App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
}
*/