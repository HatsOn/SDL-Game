
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
	App->tileMap->sceneActive = false;
	sceneActive = true;
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


	score.x = 0;
	score.y = 0;
	score.h = 64;
	score.w = 256;

	prepareTiles();

	

	App->bombs->Enable();
	App->player->Enable();
	App->boss->Enable();

	return 1;



	//	isSpeedPowerUp = false;


}



void ModuleTileMapBoss::prepareTiles()
{
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
	sceneActive = false;
	App->bombs->Disable();
	App->player->Disable();
	App->boss->Disable();
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
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile29, 0.75f);
			}

			if (map.tile[x][y] == 1)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile30, 0.75f);
			}

			if (map.tile[x][y] == 2)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile31, 0.75f);
			}

			if (map.tile[x][y] == 3)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile32, 0.75f);
			}

			if (map.tile[x][y] == 4)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile33, 0.75f);
			}

			if (map.tile[x][y] == 5)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile34, 0.75f);
			}

			if (map.tile[x][y] == 50)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile35, 0.75f);
			}

			if (map.tile[x][y] == 7)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile36, 0.75f);
			}

			if (map.tile[x][y] == 8)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile37, 0.75f);
			}

			if (map.tile[x][y] == 9)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile38, 0.75f);
			}
			if (map.tile[x][y] == 10)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile39, 0.75f);
			}

			if (map.tile[x][y] == 11)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile40, 0.75f);
			}

			if (map.tile[x][y] == 12)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile41, 0.75f);
			}

			if (map.tile[x][y] == 13)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile42, 0.75f);
			}

			if (map.tile[x][y] == 14)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile43, 0.75f);
			}

			if (map.tile[x][y] == 15)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile44, 0.75f);
			}

			if (map.tile[x][y] == 16)
			{
				App->renderer->Blit(tilesReference, x*TILE_SIZE, GUIOffset + y*TILE_SIZE, &tile45, 0.75f);
			}

			


		}
	}

	//App->renderer->Blit(portalImg, 3 * TILE_SIZE, GUIOffset + 3 * TILE_SIZE, &portal, 0.75f);
	//App->renderer->Blit(enemyImg, 9 * TILE_SIZE, GUIOffset + 4 * TILE_SIZE, &enemy1, 0.75f);

	App->renderer->Blit(scoreImg, 0 * TILE_SIZE, 0 * TILE_SIZE, &score, 0.75f);
	//App->player->Enable();
}

void ModuleTileMapBoss::OnCollision(Collider* c1, Collider* c2)
{
	


}


update_status ModuleTileMapBoss::Update()
{
	if (App->tileMap->IsEnabled())
		App->tileMap->Disable();
	BuildMap();
	App->tileMap->sceneActive = false;
	sceneActive = true;
	

	return UPDATE_CONTINUE;
}

