#pragma once


#include "Module.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

class bomb : public Module
{
public:
	int timer;
	p2Point<int> p;
	p2DynArray<Particle> particulas;
	
	bomb(Application* app, bool start_enabled);

};