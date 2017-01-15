#include "Chef.h"
#include "EntityManager.h"
#define IDLE_MSG "New order!"
#define RECEIVEORDER_MSG ""
#define COOK_MSG ""
#define CALLWAITER_MSG "On the way!"
#define DELAY_TIME 2.f
Chef::Chef()
{
    Name = "Chef";
    state = Cook;
    state_delay_timer = 0;
    EntityManager::GetInstance()->AddEntity(this);
}

Chef::~Chef()
{
}

void Chef::Init(Vector3 startpos)
{
    Position = startpos;
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
        EntityManager::GetInstance()->Talk_to(this, "Waiter", "Food's ready!");
        break;
    case Chef::CallWaiter:
        if (InputMsg != CALLWAITER_MSG)
            return;
        state = Idle;
        break;
    default:
        break;
    }
    state_delay_timer = 0.f;
    InputMsg = "";
}