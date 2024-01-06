#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics3D.h"
#include "pipe.h"
#include "p2List.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	box = Cube(1, 1, 1);
	box.SetPos(1, 1, 1);
	App->physics->AddBody(box, 1.0f);

	coinFx = App->audio->LoadFx("Assets/coin.wav");


	for (int i = 0; i < 20; ++i) {
		
		Cylinder cc = Cylinder(1.0f, 0.2f);
		cc.SetPos(i*12, 1.5f, i*5);
		Coin* c = App->physics->AddCoin(cc);
		myCoins.add(c);
		c->Shape->color = Color(1, 1, 0, 1);
		c->collision_listeners.add(this);

	}

	cub1 = new Cube(10, 10, 10);
	cub1->SetPos(0, 0, 2);
	cub2 = new Cube(5, 5, 5);
	cub2->SetPos(0, 1, 2);

	
	for (int i = 0; i < 1; ++i) {

		Cylinder c2 = Cylinder(2, 4);
		c2.SetPos(i * -4, 0, 20);
		Pipe* p = App->physics->AddPipe(c2,50000);
		myPipes.add(p);


		p->Shape2->SetPos(i*-4 + 2, 2, 20);

		p->collision_listeners.add(this);

	}


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	p2List_item<Coin*>* currentItem = myCoins.getFirst();

	while (currentItem != NULL ) {
		
		if (currentItem->data->pendingToDelete == false) {
			currentItem->data->Update();



			btVector3 coinPos = currentItem->data->GetPosition();
			btVector3 carPos = App->player->vehicle->GetPosition();
			float Xdistance = abs(coinPos.x()) - abs(carPos.x());
			float Ydistance = abs(coinPos.y()) - abs(carPos.y());
			float Zdistance = abs(coinPos.z()) - abs(carPos.z());

			// Homebrew collision detection for sensors
			if ((Xdistance > -2 && Xdistance < 2) && (Ydistance > -2 && Ydistance < 2) && (Zdistance > -2 && Zdistance < 2) && !currentItem->data->pendingToDelete) {
				LOG("car touch coing");
				currentItem->data->pendingToDelete = true;

				currentItem = currentItem->next;
				App->audio->PlayFx(coinFx);
				App->player->extraAcceleration += 50;
				App->player->coins++;

			}
			else {
				currentItem = currentItem->next;
			}
		}
		else {
			currentItem = currentItem->next;
		}
	}



	p2List_item<Pipe*>* currentItemP = myPipes.getFirst();

	while (currentItemP != NULL) {

		
		  //  currentItemP->data->Shape2->SetPos(currentItemP->data->Shape->GetPos().x, currentItemP->data->Shape->GetPos().y + 4, currentItemP->data->Shape->GetPos().z);
		    currentItemP->data->Update();



		
		
			currentItemP = currentItemP->next;
		
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{


	LOG("Collision");
}

