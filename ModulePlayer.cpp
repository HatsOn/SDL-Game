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
	speed.x = 1;
	speed.y = 1;

	// 
	bombPower = 1;


	// idle animation (just the bomberman
	idle.frames.PushBack({72, 46, 15, 23});

	// move upwards
	up.frames.PushBack({89, 21, 15, 23});
	up.frames.PushBack({57, 21, 15, 23});
	up.loop = true;
	up.speed = 0.1f;
	
	// Move down
	down.frames.PushBack({56, 46, 15, 24});
	down.frames.PushBack({88, 46, 15, 24});
	
	down.loop = true;
	down.speed = 0.1f;


	// move right
	right.frames.PushBack({ 106, 47, 16, 24 });
	right.frames.PushBack({ 122, 48, 16, 23 });
	right.frames.PushBack({ 139, 49, 16, 22 });
	right.loop = true;
	right.speed = 0.1f;

	// Move left
	left.frames.PushBack({ 36, 47, 16, 22 });
	left.frames.PushBack({ 19, 45, 15, 23 });
	left.frames.PushBack({ 3, 44, 16, 24 });
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
	position.x = 48;
	position.y = GUIOffset + 16;
	playerCollider.x = 48;
	playerCollider.y = GUIOffset + 26;
	speed.x = 0;
	speed.y = 0;
	collider = App->collision->AddCollider({ (playerCollider.x), (playerCollider.y), 16, 16 }, COLLIDER_PLAYER, this);
	

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
		directionSide = DIRECTIONLEFT;

	//Make collider follow player's position

		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}



	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{

		directionSide = DIRECTIONRIGHT;
	
	

		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{

		directionVertical = DIRECTIONDOWN;
		
		

		if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
	
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{

		directionVertical = DIRECTIONUP;

		
		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}

		
	}

	

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		int delay = 100;
		bombPosition.x = position.x;
		bombPosition.y = position.y;
		/*last_bomb = */App->particles->AddParticle(App->particles->bomb, bombPosition.x, bombPosition.y, COLLIDER_PLAYER_SHOT);

		LOG("bomba");
	}
	

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
	{
		directionVertical = NODIRECTIONVERTICAL;
		directionSide = NODIRECTIONSIDE;
		current_animation = &idle;
		
	}


	

	if (bombOn)
	{
		App->renderer->Blit(bombs, bombPosition.x, bombPosition.y, &(bombAnimation->GetCurrentFrame()));

	}

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	
		leftRightCollision(directionSide);
		upDownCollision(directionVertical);

	
	
	UpdatePosition();

	directionSide = NODIRECTIONSIDE;
	directionVertical = NODIRECTIONVERTICAL;
	return UPDATE_CONTINUE;
}
void ModulePlayer::UpdatePosition()
{
	position.y += speed.y;
	position.x += speed.x;
	playerCollider.x += speed.x;
	playerCollider.y += speed.y;

	collider->SetPos(playerCollider.x, playerCollider.y);

}


void ModulePlayer::leftRightCollision(const LookingLeftRight directionSide)
{ 
	
	
	if (directionSide == 0)//Left
	{
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][(playerCollider.y) / TILE_SIZE]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][(playerCollider.y + 15) / TILE_SIZE]))
		{

			speed.x = 0;

		}
		else
		{
			speed.x = -1;
		}
	}

	if (directionSide == 1)//Right
	{
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 17) / TILE_SIZE][(playerCollider.y) / TILE_SIZE]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 17) / TILE_SIZE][(playerCollider.y + 15) / TILE_SIZE]))
		{

			speed.x = 0;
		
		}
		else
		{
			speed.x = 1;
		}
	}

	if (directionSide == 2)//Idle
	{
	
		speed.x = 0;
	}

}

void ModulePlayer::upDownCollision(const LookingUpDown directionVertical)
{ 
	if (directionVertical == 0)//Up
	{
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][(playerCollider.y - 1) / TILE_SIZE]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15) / TILE_SIZE][(playerCollider.y - 1) / TILE_SIZE]))
		{
			speed.y = 0;
			
		}
		else
		{
			speed.y = -1;
		}
	}

	if (directionVertical == 1)//Down
	{
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][(playerCollider.y + 16) / TILE_SIZE]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15) / TILE_SIZE][(playerCollider.y + 16) / TILE_SIZE]))
		{
			speed.y = 0;
			
		}
		else
		{
			speed.y = 1;
		}
	}

	if (directionVertical == 2)//Idle
	{
		speed.y = 0;
	}

}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	
	

	if (c2->type == COLLIDER_PLAYER_EXPLOSION || c2->type == COLLIDER_ENEMY)
	{
		
	}
	if (c2->type == COLLIDER_FINISH)
	{
		LOG("PORTAL ACTIVADO");
		//App->player->Disable();
		App->fade->FadeToBlack(App->tileMap, App->scene_intro);
		
	}

}


void ModulePlayer:: isWalkable()
{
	positionTileMapUpperLeftCorner.x = (position.x) / TILE_SIZE;
	positionTileMapUpperLeftCorner.y = (position.y) / TILE_SIZE;

	positionTileMapUpperRightCorner.x = (position.x + 15) / TILE_SIZE;
	positionTileMapUpperRightCorner.y = (position.y) / TILE_SIZE;

	positionTileMapLowerLeftCorner.x = (position.x) / TILE_SIZE;
	positionTileMapLowerLeftCorner.y = (position.y + 23) / TILE_SIZE;

	positionTileMapLowerRightCorner.x = (position.x + 15) / TILE_SIZE;
	positionTileMapLowerRightCorner.y = (position.y + 23) / TILE_SIZE;

	positionTileMapMid.x = (position.x + 8) / TILE_SIZE;
	positionTileMapMid.y = (position.y + 16) / TILE_SIZE;

	if (App->tileMap->map.tile[positionTileMapUpperLeftCorner.x][positionTileMapUpperLeftCorner.y] == 10 || App->tileMap->map.tile[positionTileMapUpperRightCorner.x][positionTileMapUpperRightCorner.y] == 10)
	{
		speed.x = 1;
		speed.y = 0;
	}
	if (App->tileMap->map.tile[positionTileMapLowerLeftCorner.x][positionTileMapLowerLeftCorner.y] == 10 || App->tileMap->map.tile[positionTileMapUpperLeftCorner.x][positionTileMapUpperLeftCorner.y] == 10 || App->tileMap->map.tile[positionTileMapMid.x][positionTileMapMid.y] == 10)
	{
		speed.x = 0;
		speed.y = 1;
	}
	if (App->tileMap->map.tile[positionTileMapLowerLeftCorner.x][positionTileMapLowerLeftCorner.y] == 10 || App->tileMap->map.tile[positionTileMapLowerRightCorner.x][positionTileMapLowerRightCorner.y] == 10) // From top to down
	{
		speed.x = 1;
		speed.y = 0;
	}
	if (App->tileMap->map.tile[positionTileMapUpperRightCorner.x][positionTileMapUpperRightCorner.y] == 10 || App->tileMap->map.tile[positionTileMapLowerLeftCorner.x][positionTileMapLowerLeftCorner.y] == 10) // From down to top
	{
		speed.x = 1;
		speed.y = 0;
	}

	
}