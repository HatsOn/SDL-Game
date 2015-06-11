#include "Globals.h"
#include "Application.h"
#include "ModuleMap.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

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
	counter = 0;

	//App->particles->findParticle(COLLIDER_FINISH);
	graphics2 = App->textures->Load("MapV1.png");
	App->audio->PlayMusic("bombermanIntro.ogg", 0.5f);
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
	App->renderer->Blit(graphics2, 0, 0, NULL);
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->tileMap, 3.0f);
		App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
	}
	

	
	return UPDATE_CONTINUE;
}