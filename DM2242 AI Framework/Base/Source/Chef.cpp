#include "Chef.h"
#include "EntityManager.h"
#define IDLE_MSG "Here's the order!"
#define DELAY_TIME 2.f
Chef::Chef()
{
    Name = "Chef";
    state = Idle;
    state_delay_timer = 0;
    EntityManager::GetInstance()->AddEntity(this);
}

Chef::~Chef()
{
}

void Chef::Init(Vector3 startpos)
{
    Position = startpos;
    scale = 3.f;
}

void Chef::Update(double dt)
{
    if (state_delay_timer < DELAY_TIME)
        state_delay_timer += dt;
    StateChange();    

	switch (state)
	{
	case Chef::Idle:
		if (InputMsg != IDLE_MSG)
			return;
		state = ReceiveOrder;
		break;
	}
}

void Chef::StateChange()
{
    if (state_delay_timer < DELAY_TIME)
        return;
    state_delay_timer = 0.f;
    switch (state)
    {
    case Chef::ReceiveOrder:
        state = Cook;
        break;
    case Chef::Cook:
        EntityManager::GetInstance()->Talk_to(this, "Waiter", "Food's ready!");
        state = CallWaiter;  
        break;
    default:
        break;
    }
    state_delay_timer = 0.f;
    InputMsg = "";
}

std::string Chef::getState()
{
    switch (state)
    {
    case Chef::Idle:
        return "Idle";
        break;
    case Chef::ReceiveOrder:
        return "ReceiveOrder";
        break;
    case Chef::Cook:
        return "Cook";
        break;
    case Chef::CallWaiter:
        return "CallWaiter";
        break;
    default:
        break;
    }
    return "";
}

void Chef::GoIdle()
{
	state = Idle;
}