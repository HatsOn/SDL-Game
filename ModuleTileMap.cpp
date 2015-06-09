
#include "Application.h"
#include "Globals.h"
#include "ModuletileMap.h"
#include "ctype.h"

ModuleTileMap::ModuleTileMap(Application* app, bool start_Enabled) : Module(app, start_Enabled)
{

	
}


bool ModuleTileMap::Start()
{
	App->audio->PlayMusic("bombermanlvl1.ogg");
	tilesReference = App->textures->Load("BombermanTiles.png");
	portalImg = App->textures->Load("portal.png");

	App->renderer->camera.x = 0;
	App->renderer->camera.y = 0;

	portal.x = 268;
	portal.y = 64;
	portal.h = 16;
	portal.w = 16;

	Collider* portalCollider = App->collision->AddCollider({ 3*TILE_SIZE, GUIOffset + 3*TILE_SIZE, 16, 16 }, COLLIDER_FINISH);

	enemyImg = App->textures->Load("portal.png");

	enemy1.x = 3;
	enemy1.y = 2;
	enemy1.h = 24;
	enemy1.w = 16;

	Collider* enemy1Collider = App->collision->AddCollider({ 9 * TILE_SIZE, GUIOffset + 4 * TILE_SIZE, 16, 24 }, COLLIDER_ENEMY);

	prepareTiles();

	return 1;
	
	App->bombs->Enable();
	App->player->Enable();

}


void ModuleTileMap::prepareTiles()
{

	tile1.x = 255;
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

	tile9.x = 255;
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


	tile17.x = 255;
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

		}
	}

	App->renderer->Blit(portalImg, 3 * TILE_SIZE, GUIOffset + 3 * TILE_SIZE, &portal, 0.75f);
	App->renderer->Blit(enemyImg, 9 * TILE_SIZE, GUIOffset + 4 * TILE_SIZE, &enemy1, 0.75f);
	App->player->Enable();
}

void ModuleTileMap::CollisionMap()
{
	int x, y;



	for (y = 0; y<MAX_MAP_Y; y++)
	{
		for (x = 0; x<MAX_MAP_X; x++)
		{
			if (map.tile[x][y] == 0)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 14, 14 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 1)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 2)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 3)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 4)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 5)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 6)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 7)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 8)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 9)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}
			if (map.tile[x][y] == 10)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 11)
			{
				//App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 12)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 13)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 14)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 15)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 16)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 17)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 18)
			{
				App->collision->AddCollider({ x*TILE_SIZE, y*TILE_SIZE, 16, 16 }, COLLIDER_WALL, this);
			}

			if (map.tile[x][y] == 19)
			{
			}

			if (map.tile[x][y] == 20)
			{
			}

			if (map.tile[x][y] == 21)
			{
			}

		}
	}
}

update_status ModuleTileMap::Update()
{

	BuildMap();
	
	return UPDATE_CONTINUE;
}

