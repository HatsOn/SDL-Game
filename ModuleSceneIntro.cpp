#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;
	positionZepelin.setPosition(200, 0);
	//Animation zepelin
	zepelin.frames.PushBack({ 0, 0, 71, 40 });
	zepelin.frames.PushBack({ 0, 41, 71, 40 });
	zepelin.frames.PushBack({ 0, 82, 71, 40 });
	zepelin.loop = true;
	zepelin.speed = 0.05f;

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//App->particles->findParticle(COLLIDER_FINISH);
	graphics = App->textures->Load("buildings.png");
	zepelin2 = App->textures->Load("planes.png");
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
update_status ModuleSceneIntro::Update(){
	
	// Draw everything --------------------------------------	

	current_animation = &zepelin;

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->audio->PlayFx(select_fx);
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->map, 3.0f);
	}
	else if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_UP)
	{
		App->audio->PlayFx(select_fx);
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->map, 3.0f);
	}

	App->renderer->Blit(graphics, 0, 0, NULL);
	App->renderer->Blit(zepelin2, positionZepelin.x, positionZepelin.y, &(current_animation->GetCurrentFrame()));
	if (positionZepelin.x > -71)
	{
		positionZepelin.x--;
	}
	

	return UPDATE_CONTINUE;
}