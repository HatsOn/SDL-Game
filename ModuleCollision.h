#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include "Module.h"
#include "p2List.h"
#include "SDL\include\SDL.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_BOSS,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_PLAYER_EXPLOSION,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_FINISH,
	COLLIDER_SPEEDPOWERUP,
	COLLIDER_SIZEXPLOSIONPOWERUP,
	COLLIDER_NUMEXPLOSIONPOWERUP,
	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	Module* callback;
	int n;
	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(SDL_Rect r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision(Application* app, bool start_enabled = true);
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = NULL);
	void DrawDebug(Collider* col);

private:

	p2List<Collider*>	colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;
};

#endif // __ModuleCollision_H__