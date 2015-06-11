
#include "Application.h"
#include "Globals.h"
#include "ModuleTileMapBoss.h"
#include "ctype.h"
#include <time.h>

ModuleTileMapBoss::ModuleTileMapBoss(Application* app, bool start_Enabled) : Module(app, start_Enabled)
{


}


bool ModuleTileMapBoss::Start()
{
	//LoadMap("DebugLevel.txt");
	LoadMap("BossLevel.txt");
	//LoadMap("firstLevel.txt");

	PrintMap();

	App->audio->PlayMusic("Boss.ogg");
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
		enemies[i].collider = App->collision->AddCollider({ enemies[i].position.x, enemies[i].position.y + 8, 16, 16 }, COLLIDER_ENEMY, this);
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
	App->boss->Enable();
	deathCount = 0;

	return 1;



	//	isSpeedPowerUp = false;


}

void ModuleTileMapBoss::paintEnemies()
{
	enemyImg = App->textures->Load("portal.png");

	rEnemy1.x = 3;
	rEnemy1.y = 2;
	rEnemy1.h = 24;
	rEnemy1.w = 16;

	enemy1.position.x = 10 * 16;
	enemy1.position.y = 11 * 16;

	enemy2.position.x = 3 * 16;
	enemy2.position.y = 8 * 16 + 8;

	enemy3.position.x = 10 * 16;
	enemy3.position.y = 6 * 16 + 8;

	enemies.PushBack(enemy1);
	enemies.PushBack(enemy2);
	enemies.PushBack(enemy3);


	/*enemy1.x = 11 * 16;
	enemy1.y = (9 + 4) * 16;
	enemy1.h = 24;
	enemy1.w = 16;*/

}

void ModuleTileMapBoss::moveEnemy()
{
	for (int i = 0; i < enemies.Count(); i++)
	{


		leftRightCollision(&enemies[i], enemies[i].directionSide);
		UpDownCollision(&enemies[i], enemies[i].directionVertical);




		enemies[i].position.x += enemies[i].speed.x;
		enemies[i].position.y += enemies[i].speed.y;
	}
}

void ModuleTileMapBoss::leftRightCollision(enemy* e, LookingLeftRight& direction)
{

	if (direction == 0)
	{
		if (App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x - 1) / TILE_SIZE][((e->collider->rect.y) / TILE_SIZE) - SCOREOFFSET]) || App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x - 1) / TILE_SIZE][((e->collider->rect.y + 15) / TILE_SIZE) - SCOREOFFSET]))
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

		if (App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x + 15 + 1) / TILE_SIZE][((e->collider->rect.y) / TILE_SIZE) - SCOREOFFSET]) || App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x + 15 + 1) / TILE_SIZE][((e->collider->rect.y + 15) / TILE_SIZE) - SCOREOFFSET]))
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

void ModuleTileMapBoss::UpDownCollision(enemy* e, LookingUpDown& direction)
{

	if (direction == 0)
	{
		if (App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x) / TILE_SIZE][((e->collider->rect.y - 1) / TILE_SIZE) - SCOREOFFSET]) || App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x + 15) / TILE_SIZE][((e->collider->rect.y - 1) / TILE_SIZE) - SCOREOFFSET]))
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

		if (App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x) / TILE_SIZE][((e->collider->rect.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET]) || App->tileBoss->nonWalkableTiles.isThere(App->tileBoss->map.tile[(e->collider->rect.x + 15) / TILE_SIZE][((e->collider->rect.y + 15 + 1) / TILE_SIZE) - SCOREOFFSET]))
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




void ModuleTileMapBoss::prepareTiles()
{
	//---------------------- BOSS
	// --- 1
	tile1.x = 835;
	tile1.y = 32;
	tile1.h = 16;
	tile1.w = 16;

	tile2.x = 835;
	tile2.y = 49;
	tile2.h = 16;
	tile2.w = 16;

	tile3.x = 835;
	tile3.y = 66;
	tile3.h = 16;
	tile3.w = 16;

	tile4.x = 835;
	tile4.y = 83;
	tile4.h = 16;
	tile4.w = 16;
	// --- 2
	tile5.x = 852;
	tile5.y = 32;
	tile5.h = 16;
	tile5.w = 16;

	tile6.x = 852;
	tile6.y = 49;
	tile6.h = 16;
	tile6.w = 16;

	tile7.x = 852;
	tile7.y = 66;
	tile7.h = 16;
	tile7.w = 16;

	tile8.x = 852;
	tile8.y = 83;
	tile8.h = 16;
	tile8.w = 16;
	// --- 3
	tile9.x = 869;
	tile9.y = 32;
	tile9.h = 16;
	tile9.w = 16;

	tile10.x = 869;
	tile10.y = 49;
	tile10.h = 16;
	tile10.w = 16;

	tile11.x = 869;
	tile11.y = 66;
	tile11.h = 16;
	tile11.w = 16;

	tile12.x = 869;
	tile12.y = 83;
	tile12.h = 16;
	tile12.w = 16;
	// --- 4
	tile13.x = 886;
	tile13.y = 32;
	tile13.h = 16;
	tile13.w = 16;

	tile14.x = 886;
	tile14.y = 49;
	tile14.h = 16;
	tile14.w = 16;

	tile15.x = 886;
	tile15.y = 66;
	tile15.h = 16;
	tile15.w = 16;

	tile16.x = 886;
	tile16.y = 83;
	tile16.h = 16;
	tile16.w = 16;
	// --- 5
	tile17.x = 903;
	tile17.y = 32;
	tile17.h = 16;
	tile17.w = 16;

	tile18.x = 903;
	tile18.y = 49;
	tile18.h = 16;
	tile18.w = 16;


	//---------------------- BOSS

	nonWalkableTiles.PushBack(0);
	nonWalkableTiles.PushBack(1);
	nonWalkableTiles.PushBack(2);
	nonWalkableTiles.PushBack(3);
	nonWalkableTiles.PushBack(4);
	nonWalkableTiles.PushBack(5);
	//nonWalkableTiles.PushBack(6);
	nonWalkableTiles.PushBack(7);


	srand(time(NULL));



}








bool ModuleTileMapBoss::Init()
{
	LOG("TILE INITIATION");

	//CollisionMap();
	return true;

}

void ModuleTileMapBoss::LoadMap(char* name)
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

void ModuleTileMapBoss::PrintMap()const
{
	for (int y = 0; y<MAX_MAP_Y; y++)
	{
		for (int x = 0; x<MAX_MAP_X; x++)
		{
			LOG("%d", map.tile[x][y]);
		}
	}

}


bool ModuleTileMapBoss::CleanUp()
{
	enemies.Clear();
	App->bombs->Disable();
	App->player->Disable();
	return 0;
}


void ModuleTileMapBoss::BuildMap()
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

	//App->renderer->Blit(portalImg, 3 * TILE_SIZE, GUIOffset + 3 * TILE_SIZE, &portal, 0.75f);
	//App->renderer->Blit(enemyImg, 9 * TILE_SIZE, GUIOffset + 4 * TILE_SIZE, &enemy1, 0.75f);
	for (int i = 0; i < enemies.Count(); i++)
	{
		App->renderer->Blit(enemyImg, enemies[i].position.x, enemies[i].position.y, &rEnemy1, 0.75f);
		enemies[i].collider->SetPos(enemies[i].position.x, enemies[i].position.y + 8);
	}

	App->renderer->Blit(scoreImg, 0 * TILE_SIZE, 0 * TILE_SIZE, &score, 0.75f);
	//App->player->Enable();
}

void ModuleTileMapBoss::OnCollision(Collider* c1, Collider* c2)
{
	/*if (c2->type == COLLIDER_PLAYER_EXPLOSION)
	{
	switch (c1->n)
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
	}*/


	for (int i = 0; i < enemies.Count(); i++)
	{
		if (enemies[i].collider == c1)
		{
			enemies[i].collider->SetPos(-101, 101);
			enemies.Pop(enemies[i]);
			App->player->enemiesAlive--;
			break;
		}
	}
}


update_status ModuleTileMapBoss::Update()
{

	BuildMap();

	moveEnemy();

	return UPDATE_CONTINUE;
}

