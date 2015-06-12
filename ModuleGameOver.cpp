#include "Globals.h"
#include "Application.h"
#include "ModuleGameOver.h"


ModuleGameOver::ModuleGameOver(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	gameover.frames.PushBack({ 0, 0, 256, 272 });
	gameover.frames.PushBack({ 256, 0, 256, 272 });
	gameover.frames.PushBack({ 512, 0, 256, 272 });
	gameover.loop = true;
	gameover.speed = 0.05f;

}

ModuleGameOver::~ModuleGameOver()
{}

// Load assets
bool ModuleGameOver::Start()
{
	LOG("Loading GameOver assets");
	bool ret = true;


	//App->particles->findParticle(COLLIDER_FINISH);
	graphics = App->textures->Load("gameover.png");

	App->audio->PlayMusic("Game_Over.ogg", 0.5f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleGameOver::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleGameOver::Update()
{
	current_animation = &gameover;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->scene_intro, 3.0f);
	}


	App->renderer->Blit(graphics, 0, 0, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
