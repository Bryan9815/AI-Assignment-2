#include "Customer.h"

Customer::Customer()
{
	Name = "Customer";
}


Customer::~Customer()
{
	Delete();
}

void Customer::Init(EntityManager* EManager, float world_width, float world_height)
{
	this->EManager = EManager;
	HP = 3000;
	SetPosition(Vector3(50, 50, 0));
	this->world_height = world_height;
	this->world_width = world_width;
	Speed = 5.f;
	scale = 4.f;

	//States
	//MobSM.AddState("Chase Target");
	//MobSM.AddState("Attack");
	//MobSM.AddState("Knocked Back");
	//MobSM.AddState("Stunned");
	//MobSM.AddState("Dead");

	//MobSM.SetState("Chase Target");
}

void Customer::Init(EntityManager* EManager, float world_width, float world_height, Vector3 startpos)
{
	this->EManager = EManager;
	HP = 3000;
	SetPosition(Vector3(50, 50, 0));
	this->world_height = world_height;
	this->world_width = world_width;
	Speed = 5.f;
	scale = 4.f;

	//States
	//MobSM.AddState("Chase Target");
	//MobSM.AddState("Attack");
	//MobSM.AddState("Knocked Back");
	//MobSM.AddState("Stunned");
	//MobSM.AddState("Dead");

	//MobSM.SetState("Chase Target");
}

void Customer::Update(double dt)
{
	WrapAroundScreen();

}

void Customer::WrapAroundScreen()
{
#define OFFSET (scale * 0.5f)

	if (Position.x > world_width + OFFSET)
		Position.x = -OFFSET;
	else if (Position.x < 0 - OFFSET)
		Position.x = world_width + OFFSET;

	if (Position.y > world_height + OFFSET)
		Position.y = -OFFSET;
	else if (Position.y < -OFFSET)
		Position.y = world_height + OFFSET;
}

void Customer::Delete()
{

}