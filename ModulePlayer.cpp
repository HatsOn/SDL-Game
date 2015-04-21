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

	hasCollided = false;
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
	//collider = App->collision->AddCollider({ position.x, position.y+12, 16, 16 }, COLLIDER_PLAYER, this);
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



// Update: draw background
update_status ModulePlayer::Update()
{
	lastPosition = position;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		speed = 1;

		if (!hasCollided)
		{
			position.x -= speed;
		}
		//collider->SetPos(position.x, position.y+12);//Make collider follow player's position
		direction = Directionleft;

		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}



	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		speed = 1;

		if (!hasCollided)
		{
			LOG("COLLISION!");
			position.x += speed;
		}
		//collider->SetPos(position.x, position.y + 16);
		direction = Directionright;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		speed = 1;
		if (!hasCollided)
		{
			position.y += speed;
		}
		//collider->SetPos(position.x, position.y + 16);
		direction = Directiondown;

		if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		speed = 1;
		if (!hasCollided)
		{
			position.y -= speed;
		}
		
		//collider->SetPos(position.x, position.y + 16);
		direction = Directionup;

		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
	}


	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		int delay = 100;
		/*last_bomb = */App->particles->AddParticle(App->particles->bomb, bombPosition.x, bombPosition.y, COLLIDER_PLAYER_SHOT, 30);
		LOG("bomba");
	}


	/*if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}*/

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
	{
		speed = 0;
		current_animation = &idle;
		
	}
	// TODO 3: Actualitzar la posicio del collider del jugador perque el segueixi

	// Draw everything --------------------------------------

	/*if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{

		bombPosition.x = position.x;
		bombPosition.y = position.y+16;
		bombAnimation = &bomb;
		//App->renderer->Blit(bombs, bombPosition.x, bombPosition.y, &(bombAnimation->GetCurrentFrame()));
		bombOn = true;
	}*/

	if (bombOn)
	{
		App->renderer->Blit(bombs, bombPosition.x, bombPosition.y, &(bombAnimation->GetCurrentFrame()));
		//App->particles->AddParticle(App->particles->bomb, bombPosition.x, bombPosition.y, COLLIDER_PLAYER_SHOT, 30);
	}

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	hasCollided = false;
	isWalkable();
	return UPDATE_CONTINUE;
}

// TODO 4: Detectar colisio del jugador y retornar a la pantalla de inici
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	/*
	hasCollided = true;
	if (c2->type == COLLIDER_WALL && direction == Directionright)
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			
			//position.x -= 1;
			position.y -= speed*2;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			//position.x -= 1;
			position.y += speed*2;
		}

		else{ position.x -= 0; }
		

	}

	if (c2->type == COLLIDER_WALL && direction == Directionleft )
	{
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{

			//position.x += 1;
			position.y -= speed;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			//position.x += 1;
			position.y += speed;
		}

		else{ position.x -= 0; }
		
	}

	if (c2->type == COLLIDER_WALL && direction == Directionup)
	{
		
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{

			//position.y += 1;
			position.x += speed;

		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			//position.y += 1;
			position.x -= speed;
		}

		else{ position.x += 0; }
	}

	if (c2->type == COLLIDER_WALL && direction == Directiondown)
	{
		
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{

			position.y += speed;
			//position.x -= speed;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.y -= speed;
			//position.x += speed;
		}

		else{ position.x -= 0; }
	}
	*/
}


void ModulePlayer:: isWalkable()
{
	positionTileMap.x = position.x / TILE_SIZE;
	positionTileMap.y = position.y / TILE_SIZE;

	if (App->tileMap->map.tile[positionTileMap.x + 1][positionTileMap.y] == 10)
	{
		position = lastPosition;
	}
	if (App->tileMap->map.tile[positionTileMap.x][positionTileMap.y+1] == 10)
	{
		position = lastPosition;
	}
	if (App->tileMap->map.tile[positionTileMap.x - 1][positionTileMap.y] == 10)
	{
		position = lastPosition;
	}
	if (App->tileMap->map.tile[positionTileMap.x][positionTileMap.y - 1] == 10)
	{
		position = lastPosition;
	}


}