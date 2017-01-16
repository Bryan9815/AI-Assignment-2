#include "Customer.h"
#define DELAY_TIME 2.f

Customer::Customer()
{
	Name = "Customer";
	EntityManager::GetInstance()->AddEntity(this);
}

Customer::~Customer()
{
}

void Customer::Init()
{
	state = Find_Table;
	state_delay_timer = 0;
	scale = 3.f;
	StartPos.Set(150, 45, 0);
	Position = StartPos;
	SeatPos.Set(115, 60, 0);
}

void Customer::Update(double dt)
{
	switch (state)
	{
	case Customer::Find_Table:
		break;
	case Customer::Give_Order:
		break;
	case Customer::Wait_For_Food:
		break;
	case Customer::Eat_Food:
		break;
	case Customer::Give_Payment:
		break;
	case Customer::Leave_Restaurant:
		break;
	default:
		break;
	}
	if (state_delay_timer < DELAY_TIME)
		state_delay_timer += dt;
	StateUpdate(dt);
}

void Customer::StateUpdate(double dt)
{
	if (state_delay_timer < DELAY_TIME)
		return;
	state_delay_timer = 0.f;
	switch (state)
	{
	case Customer::Find_Table:
		break;
	case Customer::Give_Order:
		break;
	case Customer::Wait_For_Food:
		break;
	case Customer::Eat_Food:
		break;
	case Customer::Give_Payment:
		break;
	case Customer::Leave_Restaurant:
		break;
	default:
		break;
	}
	state_delay_timer = 0.f;
	InputMsg = "";
}

std::string Customer::getState()
{
	switch (state)
	{
	case Customer::Find_Table:
		return "Find_Table";
		break;
	case Customer::Give_Order:
		return "Give_Order";
		break;
	case Customer::Wait_For_Food:
		return "Wait_For_Food";
		break;
	case Customer::Eat_Food:
		return "Eat_Food";
		break;
	case Customer::Give_Payment:
		return "Give_Payment";
		break;
	case Customer::Leave_Restaurant:
		return "Leave_Restaurant";
		break;
	default:
		break;
	}
	return "";
}