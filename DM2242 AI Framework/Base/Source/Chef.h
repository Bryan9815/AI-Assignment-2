#ifndef CHEF_H
#define CHEF_H

#include "BaseEntity.h"
#include "SingletonTemplate.h"

class Chef : public BaseEntity,public Singleton<Chef>
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
    std::string getState();

	void GoIdle();
private:
    State state;
    float state_delay_timer;
};



#endif