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
		Eat_Food,
		Give_Payment,
		Leave_Restaurant,
	};

	void Init();
	void Update(double dt);

	void StateUpdate(double dt);
	std::string getState();

	void WaitForFood();
private:
	State state;
	float state_delay_timer;

	int WaypointIndex;
	bool ArrivedAtPoint = false;

	Vector3 StartPos;
	Vector3 SeatPos;
	vector <Vector3> Waypoint;
	Vector3 nextPoint;
};

#endif
