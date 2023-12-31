#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 350
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

public:

	PhysBody3D* object = nullptr;

	int coins = 0;
	int extraAcceleration = 0;
	vec3 cameraPt;

	btVector3 myDrag;

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
};