#include "Cashier.h"
#include "EntityManager.h"
#define IDLE_MSG ""
#define RECEIVEORDER_MSG ""
#define PASSORDERTOCHEF_MSG "Got it"
#define RECEIVEPAYMENT_MSG ""
#define DELAY_TIME 2.f
Cashier::Cashier()
{
    Name = "Cashier";
    state = Idle;
    state_delay_timer = 0;
}

Cashier::~Cashier()
{
}

void Cashier::Init(Vector3 startpos)
{
    Position = startpos;
    scale = 1.f;
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
        /*if (InputMsg != IDLE_MSG)
            return;*/
        state = ReceiveOrder;
        EntityManager::GetInstance()->Talk_to(this, "CustomerEntity", "Your order?");
        break;
    case Cashier::ReceiveOrder:
        if (InputMsg != RECEIVEORDER_MSG)
            return;
        state = PasssOrderToChef;
        EntityManager::GetInstance()->Talk_to(this, "Chef", "New order!");
        break;
    case Cashier::PasssOrderToChef:
        if (InputMsg != PASSORDERTOCHEF_MSG)
            return;
        state = ReceivePayment;
        break;
    case Cashier::ReceivePayment:
        if (InputMsg != RECEIVEPAYMENT_MSG)
            return;
        state = Idle;
        EntityManager::GetInstance()->Talk_to(this, "CustomerEntity", "Payment received");
        break;
    default:
        break;
    }
    state_delay_timer = 0.f;
    InputMsg = "";
}