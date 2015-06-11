
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

	App->renderer->Blit(scoreImg, 0 * TILE_SIZE, 0 * TILE_SIZE, &score, 0.75f);
	//App->player->Enable();
}

void ModuleTileMapBoss::OnCollision(Collider* c1, Collider* c2)
{
	


}


update_status ModuleTileMapBoss::Update()
{

	BuildMap();


	return UPDATE_CONTINUE;
}

