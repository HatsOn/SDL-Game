#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//App->particles->findParticle(COLLIDER_FINISH);
	graphics = App->textures->Load("BombermanIntro.png");
	App->audio->PlayMusic("bombermanIntro.ogg", 0.5f);
	App->renderer->camera.x = App->renderer->camera.y = 0;
	select_fx = App->audio->LoadFx("Select.ogg");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->audio->PlayFx(select_fx);
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->tileMap, 3.0f);
		App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_UP)
	{
		App->audio->PlayFx(select_fx);
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->tileBoss, 3.0f);
		App->audio->PlayMusic("BombermanStart.ogg", 0.5f);
	}
	

	return UPDATE_CONTINUE;
}