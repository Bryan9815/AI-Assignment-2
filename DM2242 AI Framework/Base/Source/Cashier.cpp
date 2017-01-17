#include "Cashier.h"
#include "EntityManager.h"
#define IDLE_MSG "New Order!"
#define RECEIVEPAYMENT_MSG "Here's the bill!"
#define DELAY_TIME 2.f
Cashier::Cashier()
{
    Name = "Cashier";
    state = Idle;
    state_delay_timer = 0;
    EntityManager::GetInstance()->AddEntity(this);
}

Cashier::~Cashier()
{
}

void Cashier::Init(Vector3 startpos)
{
    Position = startpos;
    scale = 3.f;
}

void Cashier::Update(double dt)
{
    if (state_delay_timer < DELAY_TIME)
        state_delay_timer += dt;
    StateChange();
    InputMsg = "";
}

void Cashier::StateChange()
{
    if (state_delay_timer < DELAY_TIME)
        return;
    
    switch (state)
    {
    case Cashier::Idle:
        if (InputMsg != IDLE_MSG && InputMsg != RECEIVEPAYMENT_MSG)
            return;
        if (InputMsg == IDLE_MSG)
            state = ReceiveOrder;
        else
            state = ReceivePayment;
        break;
    case Cashier::ReceiveOrder:
        state = PasssOrderToChef;
        break;
    case Cashier::PasssOrderToChef:
		EntityManager::GetInstance()->Talk_to(this, "Chef", "Here's the order!");
        state = Idle;
        break;
    case Cashier::ReceivePayment:
        
        state = Idle;
        break;
    default:
        break;
    }
    state_delay_timer = 0.f;
    InputMsg = "";
}

std::string Cashier::getState()
{
    switch (state)
    {
    case Cashier::Idle:
        return "Idle";
        break;
    case Cashier::ReceiveOrder:
        return "ReceiveOrder";
        break;
    case Cashier::PasssOrderToChef:
        return "PasssOrderToChef";
        break;
    case Cashier::ReceivePayment:
        return "ReceivePayment";
        break;
    default:
        break;
    }
}