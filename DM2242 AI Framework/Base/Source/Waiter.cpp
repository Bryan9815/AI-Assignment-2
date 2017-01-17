#include "Waiter.h"
#include "Customer.h"

#define DELAY_TIME 2.f
#define GIVE_ORDER_MSG "New Order!"
#define RECEIVE_FOOD_MSG "Food's ready!"
#define RECEIVE_FOOD_RESPONSE "On the way!"
#define PASS_BILL_MSG "Here's the bill!"

Waiter::Waiter()
{
	Name = "Waiter";
    EntityManager::GetInstance()->AddEntity(this);
}

Waiter::~Waiter()
{
}

void Waiter::Init()
{
	state = Idle;
	state_delay_timer = 0;
	scale = 3.f;
	StartPos.Set(90, 45, 0);
	Position = StartPos;
	TablePos.Set(107.777, 60, 0);
}

void Waiter::Update(double dt)
{
	//ChefPos = EntityManager::GetInstance()->Find("Chef")->GetPosition();
	//distFromChef = (Position - ChefPos).Length();
	CashierPos = EntityManager::GetInstance()->Find("Cashier")->GetPosition();
	distFromCashier = (Position - CashierPos).Length();
	distFromTable = (Position - TablePos).Length();
	switch (state)
	{
	case Waiter::Idle:
		if (((Position - StartPos).Length()) >= 0.5f)
		{
			Position += (StartPos - Position).Normalize() * 10 * dt;
		}
		break;
	case Waiter::Take_Order:
		if (distFromTable >= (scale + 5.f + 0.5f))
			Position += (TablePos - Position).Normalize() * 10 * dt;
		break;
	case Waiter::Give_Order_To_Cashier:
		if (distFromCashier >= (scale + scale + 0.5f))
			Position += (CashierPos - Position).Normalize() * 10 * dt;
		break;
	case Waiter::Receive_Food_From_Chef:
		if (distFromChef >= (scale + scale + 0.5f))
			Position += (ChefPos - Position).Normalize() * 10 * dt;
		break;
	case Waiter::Bring_Food_To_Table:
		if (distFromTable >= (scale + 5.f + 0.5f))
			Position += (TablePos - Position).Normalize() * 10 * dt;
		break;
	case Waiter::Pass_Bill_To_Cashier:
		if (distFromCashier >= (scale + scale + 0.5f))
			Position += (CashierPos - Position).Normalize() * 10 * dt;
		break;
	}
	if (state_delay_timer < DELAY_TIME)
		state_delay_timer += dt;
	StateUpdate(dt);
}

void Waiter::StateUpdate(double dt)
{
	if (state_delay_timer < DELAY_TIME)
		return;
	state_delay_timer = 0.f;

	Customer* customer = new Customer();

	switch (state)
	{
	case Waiter::Idle:
		if (InputMsg == RECEIVE_FOOD_MSG)
		{
			EntityManager::GetInstance()->Talk_to(this, "Chef", RECEIVE_FOOD_RESPONSE);
			state = Receive_Food_From_Chef;
		}
		break;
	case Waiter::Take_Order:
		if (distFromTable <= (scale + 5.f + 0.5f))
		{
			Customer::GetInstance()->WaitForFood();
			state = Give_Order_To_Cashier;
		}
		break;
	case Waiter::Give_Order_To_Cashier:
	{
		if (distFromCashier <= (scale + scale + 0.5f))
		{
			EntityManager::GetInstance()->Talk_to(this, "Cashier", GIVE_ORDER_MSG);
			state = Idle;
		}
		break;
	}
	case Waiter::Receive_Food_From_Chef:
	{
		if (distFromChef <= (scale + scale + 0.5f))
			state = Bring_Food_To_Table;
		break;
	}
	case Waiter::Bring_Food_To_Table:
	{
		if (distFromTable <= (scale + 5.f + 0.5f))
			state = Pass_Bill_To_Cashier;
		break;
	}
	case Waiter::Pass_Bill_To_Cashier:
		if (distFromCashier <= (scale + scale + 0.5f))
		{
			EntityManager::GetInstance()->Talk_to(this, "Cashier", PASS_BILL_MSG);
			state = Idle;
		}
		break;
	default:
		break;
	}
	state_delay_timer = 0.f;
	InputMsg = "";
}

std::string Waiter::getState()
{
    switch (state)
    {
    case Waiter::Idle:
        return "Idle";
        break;
    case Waiter::Take_Order:
        return "Take_Order";
        break;
    case Waiter::Give_Order_To_Cashier:
        return "Give_Order_To_Cashier";
        break;
    case Waiter::Receive_Food_From_Chef:
        return "Receive_Food_From_Chef";
        break;
    case Waiter::Bring_Food_To_Table:
        return "Bring_Food_To_Table";
        break;
    case Waiter::Pass_Bill_To_Cashier:
        return "Pass_Bill_To_Cashier";
        break;
    default:
        break;
    }
    return "";
}

void Waiter::TakeOrder()
{
	state = Take_Order;
}

void Waiter::PassBill()
{
	state == Pass_Bill_To_Cashier;
}