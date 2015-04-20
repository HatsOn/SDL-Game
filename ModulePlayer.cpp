#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	bombs = NULL;
	collider = NULL;
	current_animation = NULL;
	bombAnimation = NULL;
	bombOn = false;
	speed = 1;
	// idle animation (just the ship)
	idle.frames.PushBack({73, 46, 14, 24});

	// move upwards
	up.frames.PushBack({73, 22, 15, 23});
	up.frames.PushBack({90, 21, 15, 23});
	up.loop = true;
	up.speed = 0.1f;
	
	// Move down
	down.frames.PushBack({56, 48, 14, 24});
	down.frames.PushBack({88, 48, 14, 24});
	
	down.loop = true;
	down.speed = 0.1f;


	// move right
	right.frames.PushBack({ 106, 47, 14, 24 });
	right.frames.PushBack({ 123, 48, 14, 23 });
	right.frames.PushBack({ 139, 49, 16, 22 });
	right.loop = true;
	right.speed = 0.1f;

	// Move left
	left.frames.PushBack({ 36, 47, 16, 22 });
	left.frames.PushBack({ 19, 45, 15, 23 });
	left.frames.PushBack({ 4, 44, 16, 24 });
	left.loop = true;
	left.speed = 0.1f;


	//Dying
	/*die.frames.PushBack({ 343, 38, 16, 24 }); 
	die.frames.PushBack({ 361, 38, 16, 24 });
	die.frames.PushBack({ 379, 38, 16, 24 });
	die.frames.PushBack({ 397, 38, 16, 24 });
	die.speed = 0.1f;
	die.loop = false;*/

	// Set Bombs
	bomb.frames.PushBack({ 356, 151 ,16,16});
	bomb.frames.PushBack({ 373, 151, 16,16});
	bomb.frames.PushBack({390, 151, 16,16});
	bomb.loop = true;
	bomb.speed = 0.1f;


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("bombermanPC.png");
	
	bombs = App->tileMap->tilesReference;
	position.x = 75;
	position.y = 50;
	collider = App->collision->AddCollider({ position.x, position.y+16, 16, 16 }, COLLIDER_PLAYER, this);
	// TODO 2: Afegir collider al jugador

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->textures->Unload(bombs);

	return true;
}


void ModulePlayer::isWalkable()
{
	if (position.x / TILE_SIZE == App->particles->bomb.position.x / TILE_SIZE && position.y / TILE_SIZE == App->particles->bomb.position.y / TILE_SIZE)
	{
		LOG("Player dead");
		bombOn = false;
		
	}



}



// Update: draw background
update_status ModulePlayer::Update()
{
	

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed;
		collider->SetPos(position.x, position.y+16);
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}



	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
		collider->SetPos(position.x, position.y + 16);
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		collider->SetPos(position.x, position.y + 16);
		if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		collider->SetPos(position.x, position.y + 16);
		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		current_animation = &idle;

	// TODO 3: Actualitzar la posicio del collider del jugador perque el segueixi

	// Draw everything --------------------------------------

	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{

		bombPosition.x = position.x;
		bombPosition.y = position.y+16;
		bombAnimation = &bomb;
		//App->renderer->Blit(bombs, bombPosition.x, bombPosition.y, &(bombAnimation->GetCurrentFrame()));
		bombOn = true;
	}

	if (bombOn)
	{
		App->renderer->Blit(bombs, bombPosition.x, bombPosition.y, &(bombAnimation->GetCurrentFrame()));
		//App->particles->AddParticle(App->particles->bomb, bombPosition.x, bombPosition.y, COLLIDER_PLAYER_SHOT, 30);
	}

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 4: Detectar colisio del jugador y retornar a la pantalla de inici
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_WALL)
	{
		speed = 0;
		LOG("collision!");
	}
}
