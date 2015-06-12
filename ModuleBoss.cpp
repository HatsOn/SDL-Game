#include "Globals.h"
#include "Application.h"
#include "ModuleBoss.h"




ModuleBoss::ModuleBoss(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	current_animation = NULL;
	speed = 1;
	framesMove = 1;
	mazeCounter = 1;
	speedCounter = 0;
	life = 10;
	fps = 60;
	notShot = true;
	// idle animation (just the bomberman
	idle.frames.PushBack({ 525, 248, 601 - 525, 399 - 248 }); //525,248 10,35
	// move upwards
	smashing.frames.PushBack({ 525, 248, 601 - 525, 399 - 248 });
	smashing.frames.PushBack({ 606, 248, 682 - 606, 399 - 248 });
	smashing.frames.PushBack({ 687, 248, 763 - 687, 399 - 248 });
	smashing.frames.PushBack({ 768, 248, 844 - 768, 399 - 248 });
	smashing.loop = true;
	smashing.speed = 0.05f;

	damage.frames.PushBack({ 525, 248, 601 - 525, 399 - 248 });
	damage.frames.PushBack({ 849, 248, 925 - 849, 399 - 248 });
	damage.frames.PushBack({ 525, 248, 601 - 525, 399 - 248 });
	damage.frames.PushBack({ 849, 248, 925 - 849, 399 - 248 });
	damage.frames.PushBack({ 525, 248, 601 - 525, 399 - 248 });
	damage.frames.PushBack({ 849, 248, 925 - 849, 399 - 248 });
	damage.loop = true;
	damage.speed = 0.1f;



	current_animation = &idle;

}


ModuleBoss::~ModuleBoss()
{
}



bool ModuleBoss::Start()
{
	App->particles->Enable();
	App->collision->Enable();

	LOG("Loading BOSS");

	//caminar_fx = App->audio->LoadFx("caminar.ogg");

	graphics = App->textures->Load("BombermanTiles.png");
	speed = 1;
	position.x = 96-16 ;
	position.y = 64 + 16 + SCOREOFFSET;

	bossCollider = App->collision->AddCollider({ (position.x), (position.y), 55, 63 }, COLLIDER_BOSS, this);
	mazeCollider = App->collision->AddCollider({ (-100), (-100), 37, 32 }, COLLIDER_BOSS, this);
	state = CENTERED;

	App->player->bombPower = 3;

	return true;
}

bool ModuleBoss::CleanUp()
{
	LOG("Unloading player");
	App->particles->Disable();
	App->collision->Disable();
	App->textures->Unload(graphics);
	App->tileBoss->Disable();
	return true;
	
	//delete collider;

}

update_status ModuleBoss::Update()
{

	if (App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_REPEAT)
	{
		position.y -= speed;
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_REPEAT)
	{
		position.y += speed;
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT)
	{
		position.x -= speed;
	}
	else if (App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT)
	{
		position.x += speed;
	}

	/*if (App->player->position.x != position.x)
	{
		position.x +=  -1 * (App->player->position.x / App->player->position.x);
	}*/


	//position.y += 1;
	//bossCollider->SetPos(position.x+10, position.y+35);
	if (!playerInDangerZone() && speed != 0/* && mazeCounter != 1*/)
	{
		current_animation = &idle;
		mazeCollider->SetPos(-100, -100);
		if (position.y > (SCOREOFFSET * 16) - 19 && (state == LEFT || state == CENTERED))
		{
			changeBossPosition(position.x, position.y - speed);

			changeMovementState(TOP);
		}
		else if (state == TOP && position.x < 208 - 60)
		{
			changeBossPosition(position.x + speed, position.y);

			changeMovementState(RIGHT);
		}
		else if (state == RIGHT && position.y < (SCOREOFFSET * 16) + 240 - 151)
		{
			changeBossPosition(position.x, position.y + speed);

			changeMovementState(DOWN);
		}
		else if (state == DOWN && position.x > 16)
		{
			changeBossPosition(position.x - speed, position.y);

			changeMovementState(LEFT);
		}

	}
	else if (playerInDangerZone() && speed != 0/*&& mazeCounter == 1*/)
	{
		p2Point<int> tmp(8, 16);
		p2Point<int> playerCenter(App->player->position);
		playerCenter += tmp;

		tmp.setPosition(37, 140);
		p2Point<int> dangerZoneCenter(App->boss->position);
		dangerZoneCenter += tmp;

		if (dangerZoneCenter.y == playerCenter.y && dangerZoneCenter.x == playerCenter.x)
		{
			changeBossPosition(position.x, position.y);
			current_animation = &smashing;
			mazeCollider->SetPos(-100, -100);
			
		}
		if (dangerZoneCenter.x > playerCenter.x)
		{
			changeBossPosition(position.x - speed, position.y);
			//state = DOWN;
		}
		else if(dangerZoneCenter.x < playerCenter.x)
		{
			changeBossPosition(position.x + speed, position.y);
			//state = TOP;
		}
		if (dangerZoneCenter.y > playerCenter.y)
		{
			changeBossPosition(position.x, position.y - speed);
			//state = LEFT;
		}
		else if (dangerZoneCenter.y < playerCenter.y)
		{
			changeBossPosition(position.x, position.y + speed);
			//state = RIGHT;
		}	
		if (current_animation->GetCurrentFrame().x == 768)
		{
			mazeCollider->SetPos(position.x + 37 / 2, position.y + 119);
		}
	}
	else if (speed == 0)
	{
		if (speedCounter == fps)
		{
			speed = 1;
			speedCounter = 0;
			notShot = true;
		}
		speedCounter++;
	}
	



	LOG("STATE! :::: %d", state);
	/*else if (mazeCounter == 1 && playerInDangerZone())
	{
		current_animation = &smashing;
		mazeCollider->SetPos(-100, -100);
		if(current_animation->GetCurrentFrame().x == 768)
			mazeCollider->SetPos(position.x + 37/2, position.y + 119);

	}*/

	mazeCounter++;

	if (mazeCounter == 3)
	{
		mazeCounter = 1;
	}
	//current_animation = &smashing;
	
	App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	

	return UPDATE_CONTINUE;
}

void ModuleBoss::changeBossPosition(p2Point<int> _position)
{
	if (framesMove == 1)
	{
		position = _position;
		bossCollider->SetPos(_position.x, _position.y);
	}
	framesMove++;
	if (framesMove >= 3)
	{
		framesMove = 1;
	}
}
void ModuleBoss::changeBossPosition(int x, int y)
{
	if (framesMove == 1)
	{
		position.x = x;
		position.y = y;
		bossCollider->SetPos(x + 10, y + 35);
	}
	framesMove++;
	if (framesMove >= 3)
	{
		framesMove = 1;
	}	
}

void ModuleBoss::changeMovementState(bossState _state)
{
	if (position.y == (SCOREOFFSET * 16) - 19 && (state == LEFT || state == CENTERED))
	{
		state = _state;
		LOG("TOP");
	}
	else if (position.x == 208 - 60 && state == TOP)
	{
		state = _state;
		LOG("RIGHT");
	}
	else if (position.y == (SCOREOFFSET * 16) + 240 - 151 - 16 * 2 && state == RIGHT)
	{
		state = _state;
		LOG("DOWN");
	}
	else if (position.x == 16 && state == DOWN)
	{
		state = _state;
		LOG("LEFT");
	}
}

bool ModuleBoss::playerInDangerZone()
{
	bool ret = false;
	p2Point<int> tmp(8, 16);
	p2Point<int> playerCenter(App->player->position);
	playerCenter += tmp;

	tmp.setPosition(37, 119);
	p2Point<int> dangerZoneCenter(App->boss->position);
	dangerZoneCenter += tmp;


	if (abs(playerCenter.x - dangerZoneCenter.x) <= 37 && abs(playerCenter.y - dangerZoneCenter.y) <= 32)
		ret = true;
	else
		ret = false;


	return ret;	
}

void ModuleBoss::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_PLAYER_EXPLOSION)
	{
		current_animation = &damage;

		speed = 0;
		if (life > 0 && notShot)
		{
			life--;
			notShot = false;
		}
		if (life == 0)
		{
			fps = 200;
			App->fade->FadeToBlack(App->tileBoss, App->win, 5.0f);
		}

	}


}

/*bool ModuleBoss::playerInDangerZone()
{
	bool ret = false;
	p2Point<int> tmp(8, 16);
	p2Point<int> playerCenter(App->player->position);
	playerCenter += tmp;

	tmp.setPosition(37, 119);
	p2Point<int> dangerZoneCenter(App->boss->position);
	dangerZoneCenter += tmp;


	if (abs(playerCenter.x - dangerZoneCenter.x) <= 45 && ((dangerZoneCenter.y - playerCenter.y <= 119 && dangerZoneCenter.y - playerCenter.y > -32) || playerCenter.y + dangerZoneCenter.y <= 32))
		ret = true;
	else
		ret = false;

	return ret;
}*/