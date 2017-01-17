#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "EntityManager.h"

class Customer : public BaseEntity, public Singleton<Customer>
{
public:
	Customer();
	~Customer();

	enum State
	{
		Find_Table,
		Give_Order,
		Wait_For_Food,
		Give_Payment,
		Eat_Food,
		Leave_Restaurant,
		Idle,
	};

	void Init();
	void Update(double dt);

	void StateUpdate(double dt);
	std::string getState();

	void WaitForFood();
	void GetPayment();
	bool GetIdle();
private:
	State state;
	float state_delay_timer;
	bool idle;

	int WaypointIndex;
	bool ArrivedAtPoint;

	Vector3 StartPos;
	Vector3 SeatPos;
	vector <Vector3> Waypoint;
	Vector3 nextPoint;
};

#endif
