#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "EntityManager.h"

class Customer : public BaseEntity
{
public:
	Customer();
	~Customer();

	void Init(EntityManager* EManager, float world_width, float world_height);
	void Init(EntityManager* EManager, float world_width, float world_height, Vector3 startpos);
	void Update(double dt);

	void DetermineTarget();
	void WrapAroundScreen();

	StateMachine CustomerSM;
private:

	float Speed;
	float Cooldown;

	EntityManager* EManager;
};

#endif
