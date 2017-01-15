#include "Waiter.h"
#define DELAY_TIME 2.f
#define GIVE_ORDER_MSG "New Order!"
#define RECEIVE_FOOD_MSG "Food's ready!"
#define RECEIVE_FOOD_RESPONSE "On the way!"
#define PASS_BILL_MSG "Here's the bill!"

Waiter::Waiter()
{
	Name = "Waiter";
}

Waiter::~Waiter()
{
}

void Waiter::Init()
{
	state = Idle;
	state_delay_timer = 0;
}

void Waiter::Update(double dt)
{
	WrapAroundScreen();
	if (state_delay_timer < DELAY_TIME)
		state_delay_timer += dt;
	StateUpdate();
}

void Waiter::WrapAroundScreen()
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

void Waiter::StateUpdate()
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
		state = Bring_Food_To_Table;
		break;
	case Waiter::Bring_Food_To_Table:
		state = Pass_Bill_To_Cashier;
		break;
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