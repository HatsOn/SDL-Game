#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;

	zepelinFPS = 1;

	//Animation zepelin
	zepelin.frames.PushBack({ 0, 0, 71, 40 });
	zepelin.frames.PushBack({ 0, 41, 71, 40 });
	zepelin.frames.PushBack({ 0, 82, 71, 40 });
	zepelin.loop = true;
	zepelin.speed = 0.05f;
	positionZepelin.setPosition(200, 110);

	//Animation ballon
	balloonAnim.frames.PushBack({ 81, 48, 41, 74 });
	positionBalloon.setPosition(0, 40);

	//Animation zepelin3
	zepelin3Anim.frames.PushBack({ 76, 0, 29, 17 });
	positionZepelin3.setPosition(-20, 130);

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
	balloon = App->textures->Load("planes.png");
	zepelin3 = App->textures->Load("planes.png");

	introtitle = App->textures->Load("Title.png");

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
	App->textures->Unload(zepelin2);
	App->textures->Unload(balloon);
	App->textures->Unload(zepelin3);
	App->textures->Unload(introtitle);


	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update(){
	
	// Draw everything --------------------------------------	

	current_animation_zepelin1 = &zepelin;
	current_animation_balloon = &balloonAnim;
	current_animation_zepelin2 = &zepelin3Anim;

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
	

	//Zepelin2
	App->renderer->Blit(zepelin3, positionZepelin3.x, positionZepelin3.y, &(current_animation_zepelin2->GetCurrentFrame()));

	if (positionZepelin3.x < 320 && zepelinFPS == 1)
	{
		positionZepelin3.x++;
	}

	//Zepelin 1
	App->renderer->Blit(zepelin2, positionZepelin.x, positionZepelin.y, &(current_animation_zepelin1->GetCurrentFrame()));

	if (positionZepelin.x > -71 && zepelinFPS == 1)
	{
		positionZepelin.x--;
	}

	//Balloon
	App->renderer->Blit(balloon, positionBalloon.x, positionBalloon.y, &(current_animation_balloon->GetCurrentFrame()));

	if (positionBalloon.x < 320 && zepelinFPS == 1)
	{
		positionBalloon.x++;
	}
	
	App->renderer->Blit(introtitle, 0, 0, NULL);

	zepelinFPS++;

	if (zepelinFPS == 3)
	{
		zepelinFPS = 1;
	}

	return UPDATE_CONTINUE;
}