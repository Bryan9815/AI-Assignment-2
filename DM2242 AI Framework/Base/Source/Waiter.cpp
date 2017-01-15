#include "Waiter.h"
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
	Position.Set(120, 50, 0);
	TablePos.Set(117.777, 60, 0);
}

void Waiter::Update(double dt)
{
	ChefPos = EntityManager::GetInstance()->Find("Chef")->GetPosition();
	distFromChef = EntityManager::GetInstance()->FindDistanceBetweenEntities("Waiter", "Chef");
	distFromTable = (Position - TablePos).Length();
	switch (state)
	{
	case Waiter::Receive_Food_From_Chef:
		Position += (ChefPos - Position).Normalize() * 10 * dt;
		break;
	case Waiter::Bring_Food_To_Table:
		Position += (TablePos - Position).Normalize() * 10 * dt;
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
		break;
	case Waiter::Give_Order_To_Cashier:
		EntityManager::GetInstance()->Talk_to(this, "Cashier", GIVE_ORDER_MSG);
		state = Idle;
		break;
	case Waiter::Receive_Food_From_Chef:
	{
		if (distFromChef <= 1.f)
			state = Bring_Food_To_Table;
		break;
	}
	case Waiter::Bring_Food_To_Table:
	{
		if (distFromTable <= 1.f)
			state = Pass_Bill_To_Cashier;
		break;
	}
	case Waiter::Pass_Bill_To_Cashier:
		EntityManager::GetInstance()->Talk_to(this, "Cashier", PASS_BILL_MSG);
		state = Idle;
		break;
	default:
		break;
	}
	state_delay_timer = 0.f;
	InputMsg = "";
}