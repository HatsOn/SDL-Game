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
	position.y = 16;
	speed.x = 1;
	speed.y = 1;
	collider = App->collision->AddCollider({ position.x, position.y, 16, 16 }, COLLIDER_PLAYER, this);
	

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
		if  (position.x - speed.x/TILE_SIZE != position.x / TILE_SIZE )
		{	
			if (App->tileMap->map.tile[(position.x / TILE_SIZE)][position.y / TILE_SIZE] == 10 || App->tileMap->map.tile[position.x / TILE_SIZE][(position.y + 16) / TILE_SIZE] == 10)
			{

				speed.x = 0;
			}
			else
			{

				speed.x = 1;
			}

		}


		position.x -= speed.x;
		collider->SetPos(position.x, position.y);//Make collider follow player's position

		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}



	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		
		if (position.x + 16 + speed.x / TILE_SIZE != position.x / TILE_SIZE)
		{ 
			if(App->tileMap->map.tile[((position.x+16) / TILE_SIZE)][position.y / TILE_SIZE] == 10 || App->tileMap->map.tile[(position.x + 16) / TILE_SIZE][(position.y+16) / TILE_SIZE] == 10)
			{

				speed.x = 0;
			
			}
			else
			{

				speed.x = 1;
			}


	}
		position.x += speed.x;
		collider->SetPos(position.x, position.y);

		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
	
		if (position.y + 16 + speed.y / TILE_SIZE != position.y / TILE_SIZE && App->tileMap->map.tile[(position.x + 8) / TILE_SIZE][(position.y + 16) == 10])
		{
			if (App->tileMap->map.tile[position.x / TILE_SIZE][(position.y+16) / TILE_SIZE] == 10 || App->tileMap->map.tile[(position.x + 16) / TILE_SIZE][(position.y + 16) / TILE_SIZE] == 10 )
			{

				speed.y = 0;

			}
			else
			{

				speed.y = 1;
			}

		}
		else
		{
			speed.y = 1;
		}

		if(current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
		position.y += speed.y;
		collider->SetPos(position.x, position.y);
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
	
		if (position.y - speed.y / TILE_SIZE != position.y / TILE_SIZE && App->tileMap->map.tile[position.x / TILE_SIZE][(position.y / TILE_SIZE)-1] == 10)
		{

			speed.y = 0;

		}
		else
		{

			speed.y = 1;
		}

		if(current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}

		position.y -= speed.y;
		collider->SetPos(position.x, position.y);
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
		direction = NoDirection;
		current_animation = &idle;
		
	}


	

	if (bombOn)
	{
		App->renderer->Blit(bombs, bombPosition.x, bombPosition.y, &(bombAnimation->GetCurrentFrame()));

	}

	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	

	hasCollided = false;
	return UPDATE_CONTINUE;
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