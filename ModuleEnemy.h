#pragma once

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
//#include "Animation.h"
#include "Enemy.h"
class ModuleEnemy : public Module
{
	
	bool Start();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);





public: 
	//Properties
	//p2List<Enemy> enemyList;
	




};