#ifndef CASHIER_H
#define CASHIER_H

#include "BaseEntity.h"
#include "SingletonTemplate.h"

class Cashier : public BaseEntity, Singleton<Cashier>
{
public:
    Cashier();
    ~Cashier();

    enum State
    {
        Idle,
        ReceiveOrder,
        PasssOrderToChef,
        ReceivePayment,
    };

    void Init(Vector3 startpos);
    void Update(double dt);
    void StateChange();
private:
    State state;
    float state_delay_timer;
};



#endif