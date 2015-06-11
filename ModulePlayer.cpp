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
	bombOn = true;
	sizeBombPowerUpCounter = 0;
	speed.x = 1;
	speed.y = 1;
	
	
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
	dying.frames.PushBack({ 30, 75, 15, 25 });
	dying.frames.PushBack({ 48, 75, 15, 25 });
	dying.frames.PushBack({ 65, 75, 15, 25 });
	dying.frames.PushBack({ 82, 75, 15, 25 });
	dying.frames.PushBack({ 99, 75, 15, 25 });
	dying.frames.PushBack({ 117, 75, 15, 25 });
	dying.speed = 0.05f;
	dying.loop = false;

	//Ending
	ending.frames.PushBack({ 5, 132, 15, 21 });
	ending.frames.PushBack({ 22, 132, 15, 21 });
	ending.frames.PushBack({ 39, 132, 15, 21 });
	ending.frames.PushBack({ 57, 132, 15, 21 });
	ending.frames.PushBack({ 74, 132, 15, 21 });
	ending.frames.PushBack({ 91, 132, 15, 21 });
	ending.frames.PushBack({ 108, 132, 15, 21 });
	ending.frames.PushBack({ 128, 132, 15, 21 });
	ending.frames.PushBack({ 142, 132, 15, 21 });
	ending.speed = 0.05f;
	ending.loop = false;

	// Set Bombs
	bomb.frames.PushBack({ 356, 151 ,16,16});
	bomb.frames.PushBack({ 373, 151, 16,16});
	bomb.frames.PushBack({390, 151, 16,16});
	bomb.loop = true;
	bomb.speed = 0.1f;

	hasCollided = false;

	current_animation = &idle;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	App->particles->Enable();
	App->collision->Enable();
	finished = false;
	dead = false;
	bombPower = 1;
	numBombs = 1;
	enemiesAlive = 3;
	LOG("Loading player");
	canWalkLowerCorner = true;
	canWalkUpperCorner = true;
	//El personatge ha d'estar 14 segons sent invulnerable i cambiant entre color normal i blanc
	//Cada vegada mes rapid fins que es tot blanc durant l'ultim segon 

	//variables audio
	bomba_fx = App->audio->LoadFx("PosarBomba.ogg");
	powerup_fx = App->audio->LoadFx("AgafarPowerUp.ogg");
	mortpj_fx = App->audio->LoadFx("MortPJ.ogg");
	camina_fx = App->audio->LoadFx("Caminar.ogg");
	graphics = App->textures->Load("bombermanPC.png");
	
	bombs = App->tileMap->tilesReference;
	position.x = 48;
	position.y = GUIOffset + 8;
	playerCollider.x = 48;
	playerCollider.y = GUIOffset+16;
	speed.x = 0;
	speed.y = 0;
	collider = App->collision->AddCollider({ (playerCollider.x), (playerCollider.y), 16, 16 }, COLLIDER_PLAYER, this);
	dead = false;
	speedValue = 1;

	speedPowerUpCounter = 0;
	numBombPowerUpCounter = 0;

	hasCollided = false;


	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	//delete collider;

	App->particles->Disable();
	App->collision->Disable();
	//App->collision->CleanUp();
	App->textures->Unload(graphics);
	App->textures->Unload(bombs);
	App->tileMap->Disable();

	return true;
}



// Update: draw background
update_status ModulePlayer::Update()
{
	LOG("%d", bombPower);
	//LOG("Finished: %d", finished);
	lastPosition = position;

	if (dead == false && finished == false)
	{

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			directionSide = DIRECTIONLEFT;
			
				if (!App->audio->IsPlaying(audioChannel))
				{
					audioChannel = App->audio->PlayFx(camina_fx);
				}
			
			//Make collider follow player's position

			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
			}
		}



		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{

			directionSide = DIRECTIONRIGHT;

			if (!App->audio->IsPlaying(audioChannel))
			{
				audioChannel = App->audio->PlayFx(camina_fx);
			}

			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
			}

		}

		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{

			directionVertical = DIRECTIONDOWN;

			if (!App->audio->IsPlaying(audioChannel))
			{
				audioChannel = App->audio->PlayFx(camina_fx);
			}

			if (current_animation != &down)
			{
				down.Reset();
				current_animation = &down;
			}

		}

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{

			directionVertical = DIRECTIONUP;

			if (!App->audio->IsPlaying(audioChannel))
			{
				audioChannel = App->audio->PlayFx(camina_fx);
			}

			if (current_animation != &up)
			{
				up.Reset();
				current_animation = &up;
			}


		}

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			int delay = 100;
			bombPosition = bombPos(playerCollider);

			App->particles->AddParticle(App->particles->bombR, bombPosition.x, bombPosition.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->bomb, bombPosition.x, bombPosition.y, COLLIDER_PLAYER);
			App->audio->PlayFx(bomba_fx);

			//TODO: bomba centrada en una posici�
			LOG("bomba");
		}


		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
		{
			directionVertical = NODIRECTIONVERTICAL;
			directionSide = NODIRECTIONSIDE;
			current_animation = &idle;

		}

	}//Condició per si esta mort


	
	for (int i = 0; i < speedValue; i++)
	{  
	
		leftRightCollision(directionSide);
		upDownCollision(directionVertical);
	
		UpdatePosition();


		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	}

	directionSide = NODIRECTIONSIDE;
	directionVertical = NODIRECTIONVERTICAL;
	hasCollided = false;

	return UPDATE_CONTINUE;
}
void ModulePlayer::UpdatePosition()
{
	position.y += speed.y;
	position.x += speed.x;
	playerCollider.x += speed.x;
	playerCollider.y += speed.y;


	hasCollided = false;
	collider->SetPos(playerCollider.x, playerCollider.y);

}


void ModulePlayer::leftRightCollision(const LookingLeftRight directionSide)
{ 
	
	
	if (directionSide == 0)//Left
	{
		if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET]) || 
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkUpperCorner = false;
		
			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y+1) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.y++;
				playerCollider.y++;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET]))
				{
				
					position.x--;
					playerCollider.x--;
				}
				

			}

			speed.x = 0;


		}
		else
		{
			canWalkUpperCorner = true;
		}

		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y + 15) / TILE_SIZE) - SCOREOFFSET])|| 
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y + 15) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkLowerCorner = false;
			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y+16) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.y--;
				playerCollider.y--;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y + 1) / TILE_SIZE) - SCOREOFFSET]))
				{
					position.x--;
					playerCollider.x--;
				}
			

			}

			speed.x = 0;


		}
		else
		{
			canWalkLowerCorner = true;
		
		}


		if (canWalkUpperCorner && canWalkLowerCorner){ speed.x = -1; }

	
	}

	if (directionSide == 1)//Right
	{
		if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkUpperCorner = false;

			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y + 1) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.y++;
				playerCollider.y++;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET]))
				{

					position.x++;
					playerCollider.x++;
				}


			}

			speed.x = 0;


		}
		else
		{
			canWalkUpperCorner = true;
		}

		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y + 15) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x +15 + 1) / TILE_SIZE][((playerCollider.y + 15) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkLowerCorner = false;
			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.y--;
				playerCollider.y--;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]))
				{
					position.x++;
					playerCollider.x++;
				}


			}

			speed.x = 0;


		}
		else
		{
			canWalkLowerCorner = true;

		}


		if (canWalkUpperCorner && canWalkLowerCorner){ speed.x = 1; }





		/*if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET]) || 
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			
			speed.x = 0;
		
		}
		else
		{
			speed.x = 1;

		}
		*/
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

		if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkUpperCorner = false;

			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.x++;
				playerCollider.x++;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]))
				{

					position.y--;
					playerCollider.y--;
				}


			}

			speed.y = 0;


		}
		else
		{
			canWalkUpperCorner = true;
		}

		if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkLowerCorner = false;
			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.x--;
				playerCollider.x--;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]))
				{
					position.y--;
					playerCollider.y--;
				}


			}

			speed.y = 0;


		}
		else
		{
			canWalkLowerCorner = true;
		}


		if (canWalkUpperCorner && canWalkLowerCorner){ speed.y = -1; }



		/*
		if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]) || 
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET])
			||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y - 1) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			
			speed.y = 0;
			
		}
		else
		{
			speed.y = -1;

		}
	*/
	}

	if (directionVertical == 1)//Down
	{
		
		if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkUpperCorner = false;

			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x - 1) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.x++;
				playerCollider.x++;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]))
				{

					position.y++;
					playerCollider.y++;
				}


			}

			speed.y = 0;


		}
		else
		{
			canWalkUpperCorner = true;
		}

		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			canWalkLowerCorner = false;
			if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]))
			{

				hasCollided = true;

				position.x--;
				playerCollider.x--;

				if (!App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15 + 1) / TILE_SIZE][((playerCollider.y + 16) / TILE_SIZE) - SCOREOFFSET]))
				{
					position.y++;
					playerCollider.y++;
				}


			}

			speed.y = 0;


		}
		else
		{
			canWalkLowerCorner = true;

		}


		if (canWalkUpperCorner && canWalkLowerCorner){ speed.y = 1; }
		
		
		
		
		
		
		
		
		/*
		if (
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET]) || 
			App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET])
			||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x) / TILE_SIZE][((playerCollider.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET]) ||
			App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(playerCollider.x + 15) / TILE_SIZE][((playerCollider.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET])
			)
		{
			
			speed.y = 0;
			
		}
		else
		{
			speed.y = 1;

		}
	*/
	}
	
	if (directionVertical == 2)//Idle
	{
		speed.y = 0;
	}

}



void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	
	if (c2->type == COLLIDER_SPEEDPOWERUP)
	{
		App->particles->findParticle(COLLIDER_SPEEDPOWERUP);
		
		speedPowerUpCounter++;
		App->audio->PlayFx(powerup_fx);

		if (speedPowerUpCounter >= 2)
		{
			speedValue++;	
			LOG("L'speed del player es: %d", speedValue);
			speedPowerUpCounter = 0;
		}
	}

	if (c2->type == COLLIDER_SIZEXPLOSIONPOWERUP)
	{
		App->particles->findParticle(COLLIDER_SIZEXPLOSIONPOWERUP);

		sizeBombPowerUpCounter++;
		App->audio->PlayFx(powerup_fx);

		if (sizeBombPowerUpCounter >= 2)
		{
			bombPower++;
			LOG("La potencia del player es: %d", bombPower);
			sizeBombPowerUpCounter = 0;
			
		}
		
	}


	if (c2->type == COLLIDER_PLAYER_EXPLOSION && !dead)
	{
		dead = true;
		current_animation = &dying;
		App->audio->PlayFx(mortpj_fx);
		if (App->particles->portalBackup != NULL)
			App->particles->portalBackup->life = 0;
		App->fade->FadeToBlack(App->tileMap, App->scene_intro, 5.0f);
		
	}

	if (c2->type == COLLIDER_ENEMY && !dead)
	{
		dead = true;
		current_animation = &dying;		
		App->audio->PlayFx(mortpj_fx);
		App->fade->FadeToBlack(App->tileMap, App->scene_intro, 5.0f);
	}
	if (c2->type == COLLIDER_FINISH && !finished && enemiesAlive == 0)
	{
		LOG("PORTAL ACTIVADO");
		//App->player->Disable();
		finished = true;		
		position.x = c2->rect.x;
		position.y = c2->rect.y-16;
		current_animation = &ending;
		App->audio->PlayMusic("Win.ogg", 0.5f);
		App->fade->FadeToBlack(App->tileMap, App->scene_intro, 5.0f);
		App->particles->portalBackup->life = 0;
		//App->particles->findParticle(COLLIDER_FINISH);
		
	}
	if (c2->type == COLLIDER_PLAYER)
	{
		speed.SetToZero();
	}

	if (c2->type == COLLIDER_BOSS  && !dead)
	{
		dead = true;
		current_animation = &dying;
		App->audio->PlayFx(mortpj_fx);
		App->fade->FadeToBlack(App->tileMap, App->scene_intro, 5.0f);
	}

	if (c2->type == COLLIDER_NUMEXPLOSIONPOWERUP)
	{
		App->particles->findParticle(COLLIDER_NUMEXPLOSIONPOWERUP);

		numBombPowerUpCounter++;

		if (numBombPowerUpCounter >= 2)
		{
			numBombs++;
			numBombPowerUpCounter = 0;

		}
	}


}

/*

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
*/
p2Point<int> ModulePlayer::bombPos(p2Point<int> p)
{
	//Antes
	//int tileX = p.x+8 / TILE_SIZE;
	//int tileY = p.y+8 / TILE_SIZE - SCOREOFFSET;
	//Antes
	
	//Despues
	// Li sumo 8 per a trobar el punt mitg del personatge, no se si funciona, 
	// s'ha de comprobar al debug level
 	int tileX = (p.x+8) / TILE_SIZE;
	int tileY = (p.y+8) / TILE_SIZE - SCOREOFFSET;
	//Despues	
	
	
	p2Point<int> res;

	res.x = tileX * 16;
	res.y = (tileY + SCOREOFFSET) * 16;


	return res;
}

