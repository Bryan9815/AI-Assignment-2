#ifndef CUSTOMER_ENTITY_H
#define CUSTOMER_ENTITY_H

#include "EntityManager.h"

class CustomerEntity : public BaseEntity
{
public:
	CustomerEntity();
	~CustomerEntity();

	void Init(EntityManager* EManager, float world_width, float world_height);
	void Init(EntityManager* EManager, float world_width, float world_height, Vector3 startpos);
	void Update(double dt);
	void Delete();

	void DetermineTarget();
	void WrapAroundScreen();

	StateMachine CustomerSM;
private:

	float Speed;
	float Cooldown;

	EntityManager* EManager;
};

#endif
