#ifndef WAITER_ENTITY_H
#define WAITER_ENTITY_H

#include "EntityManager.h"

class WaiterEntity : public BaseEntity
{
public:
	WaiterEntity();
	~WaiterEntity();

	void Init(EntityManager* EManager, float world_width, float world_height);
	void Init(EntityManager* EManager, float world_width, float world_height, Vector3 startpos);
	void Update(double dt);
	void Delete();

	void DetermineTarget();
	void WrapAroundScreen();

	StateMachine WaiterSM;
private:

	float Speed;
	float Cooldown;

	EntityManager* EManager;
};

#endif
