#include "Globals.h"
#include "Application.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = false;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_FINISH] = false;
	matrix[COLLIDER_WALL][COLLIDER_SPEEDPOWERUP] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_EXPLOSION] = true;
	matrix[COLLIDER_WALL][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_WALL][COLLIDER_BOSS] = true;
	matrix[COLLIDER_WALL][COLLIDER_NUMEXPLOSIONPOWERUP] = false;



	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_FINISH] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_SPEEDPOWERUP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_EXPLOSION] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_SIZEXPLOSIONPOWERUP] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_BOSS] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_NUMEXPLOSIONPOWERUP] = true;


	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_FINISH] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_EXPLOSION] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_BOSS] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_NUMEXPLOSIONPOWERUP] = false;



	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_FINISH] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_BOSS] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_NUMEXPLOSIONPOWERUP] = false;





	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_FINISH] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_EXPLOSION] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_BOSS] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_NUMEXPLOSIONPOWERUP] = false;



	matrix[COLLIDER_FINISH][COLLIDER_WALL] = false;
	matrix[COLLIDER_FINISH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FINISH][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_FINISH][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_FINISH][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_FINISH][COLLIDER_FINISH] = false;
	matrix[COLLIDER_FINISH][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_FINISH][COLLIDER_PLAYER_EXPLOSION] = false;
	matrix[COLLIDER_FINISH][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_FINISH][COLLIDER_BOSS] = false;
	matrix[COLLIDER_FINISH][COLLIDER_NUMEXPLOSIONPOWERUP] = false;


	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_FINISH] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_PLAYER_EXPLOSION] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_BOSS] = false;
	matrix[COLLIDER_SPEEDPOWERUP][COLLIDER_NUMEXPLOSIONPOWERUP] = false;


	
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_FINISH] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_PLAYER_EXPLOSION] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_BOSS] = false;
	matrix[COLLIDER_SIZEXPLOSIONPOWERUP][COLLIDER_NUMEXPLOSIONPOWERUP] = false;
	

	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_FINISH] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_PLAYER_EXPLOSION] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_BOSS] = true;
	matrix[COLLIDER_PLAYER_EXPLOSION][COLLIDER_NUMEXPLOSIONPOWERUP] = false;

	matrix[COLLIDER_BOSS][COLLIDER_WALL] = true;
	matrix[COLLIDER_BOSS][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_BOSS][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_BOSS][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_BOSS][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_BOSS][COLLIDER_FINISH] = false;
	matrix[COLLIDER_BOSS][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_BOSS][COLLIDER_PLAYER_EXPLOSION] = true;
	matrix[COLLIDER_BOSS][COLLIDER_SIZEXPLOSIONPOWERUP] = true;
	matrix[COLLIDER_BOSS][COLLIDER_BOSS] = true;
	matrix[COLLIDER_BOSS][COLLIDER_NUMEXPLOSIONPOWERUP] = true;

	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_WALL] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_FINISH] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_SPEEDPOWERUP] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_PLAYER_EXPLOSION] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_SIZEXPLOSIONPOWERUP] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_BOSS] = false;
	matrix[COLLIDER_NUMEXPLOSIONPOWERUP][COLLIDER_NUMEXPLOSIONPOWERUP] = false;


}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	p2List_item<Collider*>* tmp = colliders.getFirst();
	p2List_item<Collider*>* tmp2;

	while(tmp != NULL)
	{
		tmp2 = tmp->next;
		if(tmp->data->to_delete == true)
		{
			delete tmp->data;
			colliders.del(tmp);
		}
		tmp = tmp2;
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{
	p2List_item<Collider*>* tmp = colliders.getFirst();

	Collider* c1;
	Collider* c2;

	while(tmp != NULL)
	{
		c1 = tmp->data;

		// Debug ---
		if(debug)
			DrawDebug(c1);

		p2List_item<Collider*>* tmp2 = tmp->next; // avoid checking collisions already checked
		while(tmp2 != NULL)
		{
			c2 = tmp2->data;

			if(c1->CheckCollision(c2->rect) == true)
			{
				if(matrix[c1->type][c2->type] && c1->callback) 
					c1->callback->OnCollision(c1, c2);
				
				if(matrix[c2->type][c1->type] && c2->callback) 
					c2->callback->OnCollision(c2, c1);
			}

			tmp2 = tmp2->next;
		}

		tmp = tmp->next;
	}



	// Debug ---
	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	return UPDATE_CONTINUE;
}

void ModuleCollision::DrawDebug(Collider* col)
{
	Uint8 alpha = 80;
	switch(col->type)
	{
		case COLLIDER_NONE:
		App->renderer->DrawQuad(col->rect, 255, 255, 255, alpha);
		break;
		case COLLIDER_WALL:
		App->renderer->DrawQuad(col->rect, 0, 0, 255, alpha);
		break;
		case COLLIDER_PLAYER:
		App->renderer->DrawQuad(col->rect, 0, 255, 0, alpha);
		break;
		case COLLIDER_ENEMY:
		App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
		break;
		case COLLIDER_PLAYER_SHOT:
		App->renderer->DrawQuad(col->rect, 255, 0, 0, alpha);
		break;
		case COLLIDER_PLAYER_EXPLOSION:
		App->renderer->DrawQuad(col->rect, 255, 30, 150, alpha);
		break;
		case COLLIDER_ENEMY_SHOT:
		App->renderer->DrawQuad(col->rect, 0, 255, 255, alpha);
		break;
		case COLLIDER_FINISH:
		App->renderer->DrawQuad(col->rect, 0 , 255, 125, alpha);
		break;
		case COLLIDER_SPEEDPOWERUP:
		App->renderer->DrawQuad(col->rect, 0, 255, 125, alpha);
		break;
		case COLLIDER_BOSS:
		App->renderer->DrawQuad(col->rect, 255, 255, 255, alpha);
		break;
	}
	
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	p2List_item<Collider*>* item = colliders.getLast();

	while(item != NULL)
	{
		delete item->data;
		item = item->prev;
	}

	colliders.clear();
	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect, type, callback);
	colliders.add(ret);
	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(SDL_Rect r) const
{
	return (rect.x < r.x + r.w &&
			rect.x + rect.w > r.x &&
			rect.y < r.y + r.h &&
			rect.h + rect.y > r.y);
}