#include "Chef.h"
#include "EntityManager.h"
#define IDLE_MSG "New order!"
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
        state = ReceiveOrder;        
        break;
    case Chef::ReceiveOrder:
        if (InputMsg != RECEIVEORDER_MSG)
            return;
        EntityManager::GetInstance()->Talk_to(this, "Cashier", "Got it");
        state = Cook;
        break;
    case Chef::Cook:
        if (InputMsg != COOK_MSG)
            //return;
        state = CallWaiter;
        break;
    case Chef::CallWaiter:
        if (InputMsg != CALLWAITER_MSG)
            return;
        EntityManager::GetInstance()->Talk_to(this, "Waiter", "Here's the food");
        state = Idle;
        break;
    default:
        break;
    }
    state_delay_timer = 0.f;
    InputMsg = "";
}