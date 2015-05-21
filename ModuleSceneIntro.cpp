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

	graphics = App->textures->Load("BombermanIntro.png");
	App->audio->PlayMusic("bombermanIntro.ogg", 0.5f);
	App->renderer->camera.x = App->renderer->camera.y = 0;

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
	/*// Draw everything --------------------------------------
	App->renderer->Blit(pantalla_inicio, 0, 0, &(x_background->GetCurrentFrame()));
	App->renderer->Blit(pantalla_inicio, pos_zep_h.x, pos_zep_h.y, &(x_zepelin_h->GetCurrentFrame()));
	App->renderer->Blit(pantalla_inicio, pos_zep_fire.x, pos_zep_fire.y, &(x_zepelin_fire->GetCurrentFrame()));
	App->renderer->Blit(pantalla_inicio, pos_globo.x, pos_globo.y, &(x_globo->GetCurrentFrame()));

	// Timers and Actions
	contador_titulo++;
	contador++;

	if (contador == 4)
	{
		pos_zep_fire.x -= 1;
	}

	if (contador == 6)
	{
		pos_zep_h.x += 1;
	}

	if (contador >= 8)
	{
		pos_zep_fire.x -= 1;
		pos_globo.x += 1;
		if ((pos_globo.x/8) % 2 >= 0.5f)
			pos_globo.y += 1;
		else
			pos_globo.y -= 1;
		contador = 0;
	}

	if (contador_titulo >= 250)
	{
		App->renderer->Blit(pantalla_inicio, 1, 1, &(x_bomberman_left->GetCurrentFrame()));
		App->renderer->Blit(pantalla_inicio, 1, 113, &(x_bomberman_right->GetCurrentFrame()));
	}

	if ((contador_titulo >= 300) && (menu_key == 1))
	{
		App->audio->PlayFx(ping);
		App->renderer->Blit(pantalla_inicio, 61, 153, &(x_arrow->GetCurrentFrame()));
	}

	if ((contador_titulo >= 300) && (menu_key == 2))
	{
		App->audio->PlayFx(ping);
		App->renderer->Blit(pantalla_inicio, 61, 167, &(x_arrow->GetCurrentFrame()));
	}

	if ((contador_titulo >= 300) && (menu_key == 3))
	{
		App->audio->PlayFx(ping);
		App->renderer->Blit(pantalla_inicio, 61, 181, &(x_arrow->GetCurrentFrame()));
	}

	// Keyboard
	if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_UP) && (contador_titulo >= 300) && (finish_intro == false))
	{
		menu_key--;
		if (menu_key == 0)
		{
			menu_key = 3;
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP) && (contador_titulo >= 300) && (finish_intro == false))
	{
		menu_key++;
		if (menu_key == 4)
		{
			menu_key = 1;
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP) && (contador_titulo >= 335) && (finish_intro == false))
	{
		menu_key = 1;
		finish_intro = true;
		App->audio->PlayFx(fx);
		App->fade->FadeToBlack(this, App->level_one, 3.0f);
	}*/
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		//App->tileMap->Enable();
		App->fade->FadeToBlack(this, App->tileMap, 3.0f);
	}

	return UPDATE_CONTINUE;
}