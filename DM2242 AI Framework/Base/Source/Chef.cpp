#include "Chef.h"
#include "EntityManager.h"
#define IDLE_MSG ""
#define RECEIVEORDER_MSG ""
#define COOK_MSG ""
#define CALLWAITER_MSG ""
#define DELAY_TIME 2.f
Chef::Chef()
{
    Name = "Chef";
    state = Idle;
    state_delay_timer = 0;
}

Chef::~Chef()
{
}

void Chef::Init()
{

}

void Chef::Update(double dt)
{
    if (state_delay_timer < DELAY_TIME)
        state_delay_timer += dt;
    StateChange();
    InputMsg = "";
}

void Chef::StateChange()
{
    if (state_delay_timer < DELAY_TIME)
        return;
    state_delay_timer = 0.f;
    switch (state)
    {
    case Chef::Idle:
        if (InputMsg != IDLE_MSG)
            return;

        break;
    case Chef::ReceiveOrder:
        if (InputMsg != RECEIVEORDER_MSG)
            return;
        break;
    case Chef::Cook:
        if (InputMsg != COOK_MSG)
            return;
        break;
    case Chef::CallWaiter:
        if (InputMsg != CALLWAITER_MSG)
            return;
        break;
    default:
        break;
    }
}