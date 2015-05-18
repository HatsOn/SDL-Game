#pragma once

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"
#include "Enemy.h"
class ModuleEnemy : public Module
{
	


	//Constructor

	//Methods
public:
	ModuleEnemy(Application* app, bool start_enabled = true);
	~ModuleEnemy();


	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider*, Collider*);

	void UpdatePosition();




public: 
	//Properties
	p2DynArray<Enemy> listEnemies;
	




};