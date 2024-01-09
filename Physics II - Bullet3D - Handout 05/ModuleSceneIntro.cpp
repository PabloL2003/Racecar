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

void ModuleSceneIntro::addCube(vec3 pos, vec3 size, Color rgb, float rtx, float rty, float rtz) {

	Cube cube;

	cube.SetPos(pos.x, pos.y, pos.z);
	cube.size = size;
	cube.color = rgb;

	if (rtx != 0)
		cube.SetRotation(rtx, { 1,0,0 });

	if (rty != 0)
		cube.SetRotation(rty, { 0,1,0 });

	if (rtz != 0)
		cube.SetRotation(rtz, { 0,0,1 });


	App->physics->AddBody(cube, 0);
	Borderblocks.add(cube);


}
// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//box = Cube(1000, 10, 10);
	//box.SetPos(1, 1, 1);
	//App->physics->AddBody(box, 50000.0f);

	coinFx = App->audio->LoadFx("Assets/coin.wav");


	//floor//
	addCube({ 0,0,0 }, { 200,0.2f,400 }, { 255,255,0 }, 0, 0, 0);


	//short wall//
	addCube({ -100,2,-200 }, { 50,6,6 }, { 0,255,0 }, 0, 0, 0);
	addCube({ -50,2,-200 }, { 50,6,6 }, { 0,0,255 }, 0, 0, 0);
	addCube({ 0,2,-200 }, { 50,6,6 }, { 255,0,0 }, 0, 0, 0);
	addCube({ 50,2,-200 }, { 50,6,6 }, { 0,255,0 }, 0, 0, 0);
	addCube({ 100,2,-200 }, { 50,6,6 }, { 0,0,255 }, 0, 0, 0);


	//short wall//
	addCube({ -120,2,200 }, { 50,6,6 }, { 0,255,0 }, 0, 0, 0);
	addCube({ -70,2,200 }, { 50,6,6 }, { 0,0,255 }, 0, 0, 0);
	addCube({ -20,2,200 }, { 50,6,6 }, { 255,0,0 }, 0, 0, 0);
	addCube({ 30,2,200 }, { 50,6,6 }, { 0,255,0 }, 0, 0, 0);
	addCube({ 80,2,200 }, { 50,6,6 }, { 0,0,255 }, 0, 0, 0);



	//long wall//
	addCube({ 100,2,-200 }, { 6,6,50 }, { 0,0,255 }, 0, 0, 0);
	addCube({ 100,2,-150 }, { 6,6,50 }, { 255,0,0 }, 0, 0, 0);
	addCube({ 100,2,-100 }, { 6,6,50 }, { 0,255,0 }, 0, 0, 0);
	addCube({ 100,2,-50 }, { 6,6,50 }, { 0,0,255 }, 0, 0, 0);
	addCube({ 100,2,0 }, { 6,6,50 }, { 255,0,0 }, 0, 0, 0);
	addCube({ 100,2,50 }, { 6,6,50 }, { 0,255,0 }, 0, 0, 0);
	addCube({ 100,2,100 }, { 6,6,50 }, { 0,0,255 }, 0, 0, 0);
	addCube({ 100,2,150 }, { 6,6,50 }, { 255,0,0 }, 0, 0, 0);
	addCube({ 100,2,187 }, { 6,6,25 }, { 0,255,0 }, 0, 0, 0);


	//long wall//

	addCube({ -100,2,-200 }, { 6,6,50 }, { 0,0,255 }, 0, 0, 0);
	addCube({ -100,2,-150 }, { 6,6,50 }, { 255,0,0 }, 0, 0, 0);
	addCube({ -100,2,-100 }, { 6,6,50 }, { 0,255,0 }, 0, 0, 0);
	addCube({ -100,2,-50 }, { 6,6,50 }, { 0,0,255 }, 0, 0, 0);
	addCube({ -100,2,0 }, { 6,6,50 }, { 255,0,0 }, 0, 0, 0);
	addCube({ -100,2,50 }, { 6,6,50 }, { 0,255,0 }, 0, 0, 0);
	addCube({ -100,2,100 }, { 6,6,50 }, { 0,0,255 }, 0, 0, 0);
	addCube({ -100,2,150 }, { 6,6,50 }, { 255,0,0 }, 0, 0, 0);
	addCube({ -100,2,187 }, { 6,6,25 }, { 0,255,0 }, 0, 0, 0);



	//carretera//
	//inicio//
	addCube({ -85,0,-85 }, { 20,0.3f,20 }, { 1,1,1 }, 0, 0, 0);

	//recta//
	addCube({ -85,0,0 }, { 6,0.3f,160 }, { 1,1,1 }, 0, 0, 0);

	//primera curba//
	addCube({ -84,0,84 }, { 6,0.3f,10 }, { 1,1,1 }, 0, 15, 0);
	addCube({ -81,0,91 }, { 6,0.3f,10 }, { 1,1,1 }, 0, 30, 0);
	addCube({ -76,0,96 }, { 6,0.3f,10 }, { 1,1,1 }, 0, 60, 0);
	addCube({ -66,0,98 }, { 6,0.3f,15 }, { 1,1,1 }, 0, 90, 0);
	addCube({ -56,0,96 }, { 6,0.3f,10 }, { 1,1,1 }, 0, 110, 0);

	//rampa//
	addCube({ 0,0,0 }, { 6,0.3f,60 }, { 1,1,1 }, 0, 0, 0);
	addCube({ 0,0,0 }, { 6,0.3f,60 }, { 1,1,1 }, 20, 0, 0);


	for (int i = 0; i < 20; ++i) {

		Cylinder cc = Cylinder(1.0f, 0.2f);
		cc.SetPos(i * 12, 1.5f, i * 5);
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

	p2List_item<Cube>* c = Borderblocks.getFirst();
	while (c != NULL) {
		c->data.Render();
		c = c->next;
	}


	p2List_item<Coin*>* currentItem = myCoins.getFirst();

	while (currentItem != NULL) {

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
