#ifndef WAITER_H
#define WAITER_H

#include "EntityManager.h"

class Waiter : public BaseEntity
{
public:
	Waiter();
	~Waiter();

	enum State
	{
		Idle,
		Take_Order,
		Give_Order_To_Cashier,
		Receive_Food_From_Chef,
		Bring_Food_To_Table,
		Pass_Bill_To_Cashier
	};

	void Init();
	void Update(double dt);
	void Delete();

	void DetermineTarget();
	void WrapAroundScreen();
	void StateUpdate();
private:
	State state;
	float state_delay_timer;
};

#endif
