#include "Cashier.h"
#define IDLE_MSG ""
#define RECEIVEORDER_MSG ""
#define PASSORDERTOCHEF_MSG ""
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

void Cashier::Init()
{

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
    state_delay_timer = 0.f;
    switch (state)
    {
    case Cashier::Idle:
        if (InputMsg != IDLE_MSG)
            return;
        break;
    case Cashier::ReceiveOrder:
        if (InputMsg != RECEIVEORDER_MSG)
            return;
        break;
    case Cashier::PasssOrderToChef:
        if (InputMsg != PASSORDERTOCHEF_MSG)
            return;
        break;
    case Cashier::ReceivePayment:
        if (InputMsg != RECEIVEPAYMENT_MSG)
            return;
        break;
    default:
        break;
    }
}