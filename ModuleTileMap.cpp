
#include "Application.h"
#include "Globals.h"
#include "ModuletileMap.h"
#include "ctype.h"
#include <time.h>

ModuleTileMap::ModuleTileMap(Application* app, bool start_Enabled) : Module(app, start_Enabled)
{

	
}


bool ModuleTileMap::Start()
{

	//LoadMap("DebugLevel.txt");
	LoadMap("FirstLevel.txt");
	//LoadMap("firstLevel.txt");

	PrintMap();

	mortenemic_fx = App->audio->LoadFx("MortEnemic.ogg");
	App->audio->PlayMusic("bombermanlvl1.ogg");
	tilesReference = App->textures->Load("BombermanTiles.png");
	portalImg = App->textures->Load("portal.png");
	scoreImg = App->textures->Load("Marcador.png");

	App->renderer->camera.x = 0;
	App->renderer->camera.y = 0;

	portal.x = 268;
	portal.y = 64;
	portal.h = 16;
	portal.w = 16;

	//Collider* portalCollider = App->collision->AddCollider({ 3*TILE_SIZE, GUIOffset + 3*TILE_SIZE, 16, 16 }, COLLIDER_FINISH);

	//Collider* enemy1Collider = App->collision->AddCollider({ 9 * TILE_SIZE, GUIOffset + 4 * TILE_SIZE, 16, 16 }, COLLIDER_ENEMY);

	paintEnemies();
	for (int i = 0; i < enemies.Count(); i++)
	{
		enemies[i].collider = App->collision->AddCollider({ enemies[i].position.x, enemies[i].position.y+8, 16, 16 }, COLLIDER_ENEMY, this);
	}

	score.x = 0;
	score.y = 0;
	score.h = 64;
	score.w = 256;

	prepareTiles();

	enemies[0].directionSide = NODIRECTIONSIDE;
	enemies[0].directionVertical = DIRECTIONUP;
	enemies[0].collider->n = 0;

	enemies[1].directionSide = DIRECTIONLEFT;
	enemies[1].directionVertical = NODIRECTIONVERTICAL;
	enemies[1].collider->n = 1;

	enemies[2].directionSide = DIRECTIONLEFT;
	enemies[2].directionVertical = NODIRECTIONVERTICAL;
	enemies[2].collider->n = 2;

	App->bombs->Enable();
	App->player->Enable();

	deathCount = 0;

	return 1;
	
	

//	isSpeedPowerUp = false;


}

void ModuleTileMap::paintEnemies()
{
	enemyImg = App->textures->Load("portal.png");
	
	rEnemy1.x = 3;
	rEnemy1.y = 2;
	rEnemy1.h = 24;
	rEnemy1.w = 16;

	enemy1.position.x = 10 * 16;
	enemy1.position.y = 11 * 16;

	enemy2.position.x = 3 * 16;
	enemy2.position.y = 8 * 16+8;

	enemy3.position.x = 10 * 16;
	enemy3.position.y = 6 * 16 +8;

	enemies.PushBack(enemy1);
	enemies.PushBack(enemy2);
	enemies.PushBack(enemy3);


	/*enemy1.x = 11 * 16;
	enemy1.y = (9 + 4) * 16;
	enemy1.h = 24;
	enemy1.w = 16;*/
	
}

void ModuleTileMap::moveEnemy()
{
	for (int i = 0; i < enemies.Count(); i++)
	{
	

		leftRightCollision(&enemies[i],enemies[i].directionSide);
		UpDownCollision(&enemies[i], enemies[i].directionVertical);




		enemies[i].position.x += enemies[i].speed.x;
		enemies[i].position.y += enemies[i].speed.y;
	}
}

void ModuleTileMap::leftRightCollision(enemy* e, LookingLeftRight& direction)
{

	if (direction == 0)
	{
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x - 1) / TILE_SIZE][((e->collider->rect.y) / TILE_SIZE) - SCOREOFFSET]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x - 1) / TILE_SIZE][((e->collider->rect.y + 15) / TILE_SIZE) - SCOREOFFSET]))
		{

			e->speed.x *= -1;
			direction = DIRECTIONRIGHT;
		}
		else
		{
			e->speed.x = -1;

		}
	}

	else if (direction == 1)
	{

		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x + 15 + 1) / TILE_SIZE][((e->collider->rect.y) / TILE_SIZE) - SCOREOFFSET]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x + 15 + 1) / TILE_SIZE][((e->collider->rect.y + 15) / TILE_SIZE) - SCOREOFFSET]))
		{

			e->speed.x *= -1;
			direction = DIRECTIONLEFT;
		}
		else
		{
			e->speed.x = 1;

		}

	}

	else if (direction == 2)//Idle
	{

		e->speed.x = 0;
	}

}

void ModuleTileMap::UpDownCollision(enemy* e, LookingUpDown& direction)
{

	if (direction == 0)
	{
		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x) / TILE_SIZE][((e->collider->rect.y - 1) / TILE_SIZE) - SCOREOFFSET]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x + 15) / TILE_SIZE][((e->collider->rect.y - 1) / TILE_SIZE) - SCOREOFFSET]))
		{

			e->speed.y *= -1;
			direction = DIRECTIONDOWN;
		}
		else
		{
			e->speed.y = -1;

		}

	}

	else if (direction == 1)
	{

		if (App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x) / TILE_SIZE][((e->collider->rect.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET]) || App->tileMap->nonWalkableTiles.isThere(App->tileMap->map.tile[(e->collider->rect.x + 15) / TILE_SIZE][((e->collider->rect.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET]))
		{

			e->speed.y *= -1;
			direction = DIRECTIONUP;
		}
		else
		{
			e->speed.y = 1;

		}

	}
	else if (direction == 2)//Idle
	{

		e->speed.y = 0;
	}
}




void ModuleTileMap::prepareTiles()
{

	tile1.x = 254;
	tile1.y = 15;
	tile1.h = 16;
	tile1.w = 16;


	tile2.x = 271;
	tile2.y = 15;
	tile2.h = 16;
	tile2.w = 16;

	tile3.x = 288;
	tile3.y = 15;
	tile3.h = 16;
	tile3.w = 16;


	tile4.x = 305;
	tile4.y = 15;
	tile4.h = 16;
	tile4.w = 16;


	tile5.x = 322;
	tile5.y = 15;
	tile5.h = 16;
	tile5.w = 16;


	tile6.x = 339;
	tile6.y = 15;
	tile6.h = 16;
	tile6.w = 16;


	tile7.x = 356;
	tile7.y = 15;
	tile7.h = 16;
	tile7.w = 16;


	tile8.x = 373;
	tile8.y = 15;
	tile8.h = 16;
	tile8.w = 16;
	//--------------- SECOND ROW

	tile9.x = 254;
	tile9.y = 32;
	tile9.h = 16;
	tile9.w = 16;


	tile10.x = 271;
	tile10.y = 32;
	tile10.h = 16;
	tile10.w = 16;

	tile11.x = 288;
	tile11.y = 32;
	tile11.h = 16;
	tile11.w = 16;


	tile12.x = 305;
	tile12.y = 32;
	tile12.h = 16;
	tile12.w = 16;


	tile13.x = 322;
	tile13.y = 32;
	tile13.h = 16;
	tile13.w = 16;


	tile14.x = 339;
	tile14.y = 32;
	tile14.h = 16;
	tile14.w = 16;



	tile15.x = 356;
	tile15.y = 32;
	tile15.h = 16;
	tile15.w = 16;


	tile16.x = 355;
	tile16.y = 32;
	tile16.h = 16;
	tile16.w = 16;
	//--------------- THIRD ROW


	tile17.x = 254;
	tile17.y = 49;
	tile17.h = 16;
	tile17.w = 16;


	tile18.x = 271;
	tile18.y = 49;
	tile18.h = 16;
	tile18.w = 16;


	tile19.x = 288;
	tile19.y = 49;
	tile19.h = 16;
	tile19.w = 16;


	tile20.x = 305;
	tile20.y = 49;
	tile20.h = 16;
	tile20.w = 16;



	tile21.x = 322;
	tile21.y = 49;
	tile21.h = 16;
	tile21.w = 16;


	tile22.x = 339;
	tile22.y = 49;
	tile22.h = 16;
	tile22.w = 16;

	tile23.x = 216;
	tile23.y = 15;
	tile23.h = 16;
	tile23.w = 16;

	tile24.x = 234;
	tile24.y = 15;
	tile24.h = 16;
	tile24.w = 16;

	tile25.x = 216;
	tile25.y = 32;
	tile25.h = 16;
	tile25.w = 16;

	tile26.x = 234;
	tile26.y = 32;
	tile26.h = 16;
	tile26.w = 16;

	tile27.x = 216;
	tile27.y = 49;
	tile27.h = 16;
	tile27.w = 16;

	tile28.x = 234;
	tile28.y = 49;
	tile28.h = 16;
	tile28.w = 16;
	//---------------------- BOOS
	// --- 1
	tile29.x = 835;
	tile29.y = 32;
	tile29.h = 16;
	tile29.w = 16;

	tile30.x = 835;
	tile30.y = 49;
	tile30.h = 16;
	tile30.w = 16;

	tile31.x = 835;
	tile31.y = 66;
	tile31.h = 16;
	tile31.w = 16;

	tile32.x = 835;
	tile32.y = 83;
	tile32.h = 16;
	tile32.w = 16;
	// --- 2
	tile33.x = 852;
	tile33.y = 32;
	tile33.h = 16;
	tile33.w = 16;

	tile34.x = 852;
	tile34.y = 49;
	tile34.h = 16;
	tile34.w = 16;

	tile35.x = 852;
	tile35.y = 66;
	tile35.h = 16;
	tile35.w = 16;

	tile36.x = 852;
	tile36.y = 83;
	tile36.h = 16;
	tile36.w = 16;
	// --- 3
	tile37.x = 869;
	tile37.y = 32;
	tile37.h = 16;
	tile37.w = 16;

	tile38.x = 869;
	tile38.y = 49;
	tile38.h = 16;
	tile38.w = 16;

	tile39.x = 869;
	tile39.y = 66;
	tile39.h = 16;
	tile39.w = 16;

	tile40.x = 869;
	tile40.y = 83;
	tile40.h = 16;
	tile40.w = 16;
	// --- 4
	tile41.x = 886;
	tile41.y = 32;
	tile41.h = 16;
	tile41.w = 16;

	tile42.x = 886;
	tile42.y = 49;
	tile42.h = 16;
	tile42.w = 16;

	tile43.x = 886;
	tile43.y = 66;
	tile43.h = 16;
	tile43.w = 16;

	tile44.x = 886;
	tile44.y = 83;
	tile44.h = 16;
	tile44.w = 16;
	// --- 5
	tile45.x = 903;
	tile45.y = 32;
	tile45.h = 16;
	tile45.w = 16;

	tile45.x = 903;
	tile45.y = 49;
	tile45.h = 16;
	tile45.w = 16;

	
	//---------------------- BOSS

	nonWalkableTiles.PushBack(0);
	nonWalkableTiles.PushBack(1);
	nonWalkableTiles.PushBack(2);
	nonWalkableTiles.PushBack(3);
	nonWalkableTiles.PushBack(4);
	nonWalkableTiles.PushBack(5);
	nonWalkableTiles.PushBack(6);
	nonWalkableTiles.PushBack(7);
	nonWalkableTiles.PushBack(8);
	nonWalkableTiles.PushBack(9);
	nonWalkableTiles.PushBack(10);
	nonWalkableTiles.PushBack(33);
	nonWalkableTiles.PushBack(12);
	nonWalkableTiles.PushBack(13);
	nonWalkableTiles.PushBack(14);
	nonWalkableTiles.PushBack(15);
	nonWalkableTiles.PushBack(16);
	nonWalkableTiles.PushBack(17);
	nonWalkableTiles.PushBack(18);
	nonWalkableTiles.PushBack(44);
	nonWalkableTiles.PushBack(55);
	nonWalkableTiles.PushBack(21);
	nonWalkableTiles.PushBack(22);
	nonWalkableTiles.PushBack(23);
	nonWalkableTiles.PushBack(24);
	nonWalkableTiles.PushBack(25);
	nonWalkableTiles.PushBack(26);
	nonWalkableTiles.PushBack(27);

	nonWalkableTiles.PushBack(29);
	nonWalkableTiles.PushBack(30);
	nonWalkableTiles.PushBack(31);
	nonWalkableTiles.PushBack(32);
	nonWalkableTiles.PushBack(33); 
	nonWalkableTiles.PushBack(34);
	nonWalkableTiles.PushBack(36);

	srand(time(NULL));

	

}








bool ModuleTileMap::Init()
{
	LOG("TILE INITIATION");

	//LoadMap("DebugLevel.txt");
	//LoadMap("FirstLevel.txt");
	LoadMap("firstLevel.txt");

	PrintMap();


	//CollisionMap();
	return true;
	
}

void ModuleTileMap::LoadMap(char* name)
{
	int x, y;
	FILE *fp;
	char tile[10];
	fp = fopen(name, "rb");

	/* If we can't open the map then exit */

	if (fp == NULL)
	{
		LOG("Failed to open map %s\n", name);

		exit(1);
	}

	/* Read the data from the file into the map */

	for (y = 0; y<MAX_MAP_Y; y++)
	{
		for (x = 0; x<MAX_MAP_X; x++)
		{
			//fscanf(fp, "%s", &map.tile[x][y]);
			fscanf(fp, "%s", tile);

			map.tile[x][y] = atoi(tile);
		}
	}

	/* Close the file afterwards */

	fclose(fp);
}

void ModuleTileMap::PrintMap()const
{
	for (int y = 0; y<MAX_MAP_Y; y++)
	{
		for (int x = 0; x<MAX_MAP_X; x++)
		{
			LOG("%d", map.tile[x][y]);
		}
	}

}


bool ModuleTileMap::CleanUp()
{
	enemies.Clear();
	App->bombs->Disable();
	App->player->Disable();
	return 0;
}


void ModuleTileMap::BuildMap()
{
	int x, y;

	/* Draw the background */

	/* Draw the map */

	for (y = 0; y<MAX_MAP_Y; y++)
	{
		for (x = 0; x<MAX_MAP_X; x++)
		{
			if (map.tile[x][y] == 0)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile1, 0.75f);
			}

			if (map.tile[x][y] == 1)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile2, 0.75f);
			}

			if (map.tile[x][y] == 2)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile3, 0.75f);
			}

			if (map.tile[x][y] == 3)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile4, 0.75f);
			}

			if (map.tile[x][y] == 4)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile5, 0.75f);
			}

			if (map.tile[x][y] == 5)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile6, 0.75f);
			}

			if (map.tile[x][y] == 6)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile7, 0.75f);
			}

			if (map.tile[x][y] == 7)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile8, 0.75f);
			}

			if (map.tile[x][y] == 8)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile9, 0.75f);
			}

			if (map.tile[x][y] == 9)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile10, 0.75f);
			}
			if (map.tile[x][y] == 10)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile11, 0.75f);
			}

			if (map.tile[x][y] == 11)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile12, 0.75f);
			}

			if (map.tile[x][y] == 12)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile13, 0.75f);
			}

			if (map.tile[x][y] == 13)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile14, 0.75f);
			}

			if (map.tile[x][y] == 14)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile15, 0.75f);
			}

			if (map.tile[x][y] == 15)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile16, 0.75f);
			}

			if (map.tile[x][y] == 16)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile17, 0.75f);
			}

			if (map.tile[x][y] == 17)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile18, 0.75f);
			}

			if (map.tile[x][y] == 18)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile19, 0.75f);
			}

			if (map.tile[x][y] == 19)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile20, 0.75f);
			}

			if (map.tile[x][y] == 20)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile21, 0.75f);
			}

			if (map.tile[x][y] == 21)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile22, 0.75f);
			}
			if (map.tile[x][y] == 22)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile23, 0.75f);
			}

			if (map.tile[x][y] == 23)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile24, 0.75f);
			}

			if (map.tile[x][y] == 24)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile25, 0.75f);
			}

			if (map.tile[x][y] == 25)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile26, 0.75f);
			}

			if (map.tile[x][y] == 26)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile27, 0.75f);
			}
			if (map.tile[x][y] == 27)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile28, 0.75f);
			}


		}
	}


	for (int i = 0; i < enemies.Count(); i++)
	{
		App->renderer->Blit(enemyImg, enemies[i].position.x, enemies[i].position.y, &rEnemy1, 0.75f);
		enemies[i].collider->SetPos(enemies[i].position.x, enemies[i].position.y+8);
	}
	
	App->renderer->Blit(scoreImg, 0 * TILE_SIZE, 0 * TILE_SIZE, &score, 0.75f);
	//App->player->Enable();
}

void ModuleTileMap::OnCollision(Collider* c1, Collider* c2)
{



	if (c2->type == COLLIDER_PLAYER_EXPLOSION)
	{
		/*switch (c1->n)
		{
		case 0:
		if (deathCount > 1)
		{
		enemies.Pop(enemy1);
		c2->to_delete;
		deathCount = 0;
		}
		deathCount++;
		break;
		case 1:
		if (deathCount > 1)
		{
		enemies.Pop(enemy2);
		c2->to_delete;
		deathCount = 0;
		}
		deathCount++;
		break;
		case 2:
		if (deathCount > 1)
		{
		enemies.Pop(enemy3);
		c2->to_delete;
		deathCount = 0;
		}
		deathCount++;
		break;

		default:
		break;
		}

		}
		for (int i = 0; i < enemies.Count(); i++)
		{
		enemies[i].collider->rect.x = -160;
		enemies[i].collider->rect.y = -160;
		enemies[i].collider->to_delete;
		//enemies[i].collider->SetPos(-106, -160);
		}
		*/

		for (int i = 0; i < enemies.Count(); i++)
		{
			if (enemies[i].collider == c1)
			{
				enemies[i].collider->SetPos(-101, 101);
				enemies.Pop(enemies[i]);
				App->player->enemiesAlive--;
				App->audio->PlayFx(mortenemic_fx);
				break;
			}
		}
	}
	else if (c2->type == COLLIDER_PLAYER_SHOT)
	{
		for (int i = 0; i < enemies.Count(); i++)
		{
			if (enemies[i].collider == c1)
			{
				if (enemies[i].directionSide == DIRECTIONLEFT)
				{
					enemies[i].directionSide = DIRECTIONRIGHT;
					enemies[i].position.x += 2;
				}
				else if (enemies[i].directionSide == DIRECTIONRIGHT)
				{
					enemies[i].directionSide = DIRECTIONLEFT;
					enemies[i].position.x -= 2;
				}
				if (enemies[i].directionVertical == DIRECTIONUP)
				{
					enemies[i].directionVertical = DIRECTIONDOWN;
					enemies[i].position.y += 2;
					
				}
				else if (enemies[i].directionVertical == DIRECTIONDOWN)
				{
					enemies[i].directionVertical = DIRECTIONUP;
					enemies[i].position.y -= 2;
				}
				
			}
		}

	
	
	}
}


update_status ModuleTileMap::Update()
{

	BuildMap();
	
	moveEnemy();

	return UPDATE_CONTINUE;
}

