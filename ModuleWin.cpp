#include "Globals.h"
#include "Application.h"
#include "ModuleWin.h"


ModuleWin::ModuleWin(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	win.frames.PushBack({ 0, 0, 256, 272 });
	win.frames.PushBack({ 256, 0, 256, 272 });
	win.frames.PushBack({ 512, 0, 256, 272 });
	win.frames.PushBack({ 768, 0, 256, 272 });
	win.frames.PushBack({ 1024, 0, 256, 272 });
	win.frames.PushBack({ 1280, 0, 256, 272 });
	win.loop = true;
	win.speed = 0.05f;

}

ModuleWin::~ModuleWin()
{}

// Load assets
bool ModuleWin::Start()
{
	LOG("Loading Win assets");
	bool ret = true;


	//App->particles->findParticle(COLLIDER_FINISH);
	graphics = App->textures->Load("WinAnimate.png");

	App->audio->PlayMusic("Ending.ogg", 0.5f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleWin::CleanUp()
{
	LOG("Unloading Win scene");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleWin::Update()
{
	current_animation = &win;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->scene_intro, 3.0f);
	}


	App->renderer->Blit(graphics, 0, 0, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}
