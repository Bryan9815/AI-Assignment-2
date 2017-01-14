#ifndef CHEF_H
#define CHEF_H

#include "BaseEntity.h"
#include "SingletonTemplate.h"

class Chef : public BaseEntity, Singleton<Chef>
{
public:
    Chef();
    ~Chef();

    enum State
    {
        Idle,
        ReceiveOrder,
        Cook,
        CallWaiter
    };

    void Init(Vector3 startpos);
    void Update(double dt);
    void StateChange();
private:
    State state;
    float state_delay_timer;
};



#endif