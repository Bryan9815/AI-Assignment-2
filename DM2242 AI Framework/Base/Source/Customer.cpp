#include "Customer.h"
#include "Waiter.h"
#include "Chef.h"
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

	Waypoint.push_back(StartPos);
	Waypoint.push_back(Vector3(125, 45, 0));
	Waypoint.push_back(SeatPos);

	WaypointIndex = 1;
}

void Customer::Update(double dt)
{
	switch (state)
	{
	case Customer::Find_Table:
	{
		nextPoint = Waypoint[WaypointIndex];
		Vector3 direction = (nextPoint - Position).Normalize();
		float distance = sqrt((nextPoint.x - Position.x) * (nextPoint.x - Position.x) + (nextPoint.y - Position.y) * (nextPoint.y - Position.y));
		if (distance < (10 * dt))
		{
			Position = nextPoint;
			ArrivedAtPoint = true;
		}
		else if (!ArrivedAtPoint)
			Position += direction * 10 * dt;

		if (ArrivedAtPoint)
		{
			if (WaypointIndex == Waypoint.size() - 1)
			{
				state = Give_Order;
			}
			else
			{
				WaypointIndex++;
				ArrivedAtPoint = false;
			}
		}
		break;
	}
	case Customer::Give_Order:
	{
		Waiter::GetInstance()->TakeOrder();
		break;
	}
	case Customer::Leave_Restaurant:
	{
		nextPoint = Waypoint[WaypointIndex];
		Vector3 direction = (nextPoint - Position).Normalize();
		float distance = sqrt((nextPoint.x - Position.x) * (nextPoint.x - Position.x) + (nextPoint.y - Position.y) * (nextPoint.y - Position.y));
		if (distance < (10 * dt))
		{
			Position = nextPoint;
			ArrivedAtPoint = true;
		}
		else if (!ArrivedAtPoint)
			Position += direction * 10 * dt;

		if (ArrivedAtPoint)
		{
			if (WaypointIndex == 0)
			{
				state = Find_Table;
			}
			else
			{
				WaypointIndex--;
				ArrivedAtPoint = false;
			}
		}
		break;
	}
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
	case Customer::Eat_Food:
		state = Give_Payment;
		break;
	case Customer::Give_Payment:
		Waiter::GetInstance()->PassBill();
		state = Leave_Restaurant;
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

void Customer::WaitForFood()
{
	state = Wait_For_Food;
}