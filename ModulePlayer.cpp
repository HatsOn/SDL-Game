#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app) : Module(app)
{
	graphics = NULL;

	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.frames.PushBack({7, 14, 60, 90});
	idle.frames.PushBack({95, 15, 60, 89});
	idle.frames.PushBack({184, 14, 60, 90});
	idle.frames.PushBack({276, 11, 60, 93});
	idle.frames.PushBack({366, 12, 60, 92});
	idle.speed = 0.1f;

	// walk forward animation (arcade sprite sheet)
	forward.frames.PushBack({9, 136, 53, 83});
	forward.frames.PushBack({78, 131, 60, 88});
	forward.frames.PushBack({162, 128, 64, 92});
	forward.frames.PushBack({259, 128, 63, 90});
	forward.frames.PushBack({352, 128, 54, 91});
	forward.frames.PushBack({432, 131, 50, 89});
	forward.speed = 0.1f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.PushBack({542, 131, 61, 87});
	backward.frames.PushBack({628, 129, 59, 90});
	backward.frames.PushBack({713, 128, 57, 90});
	backward.frames.PushBack({797, 127, 57, 90});
	backward.frames.PushBack({883, 128, 58, 91});
	backward.frames.PushBack({974, 129, 57, 89});
	backward.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("ryu4.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;
	// debug camera movement --------------------------------
	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &backward;
		position.x -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->renderer->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}