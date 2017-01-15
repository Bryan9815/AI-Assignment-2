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

	void StateUpdate(double dt);
    std::string getState();
private:
	State state;
	float state_delay_timer;

	Vector3 StartPos;
	Vector3 ChefPos;
	Vector3 CashierPos;
	Vector3 TablePos;

	float distFromChef;
	float distFromTable;
	float distFromCashier;
};

#endif
