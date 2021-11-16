#ifndef COLLISION_SYSTEM_INCLUDE
#define COLLISION_SYSTEM_INCLUDE

#include "ECS/ECS.h"
#include <components.h>

class CollisionSystem : public ECS::BaseSystem
{
public:
	CollisionSystem();

	void update();
private:

	bool checkCollision(ECS::EntityID t_self, ECS::EntityID t_other);

	ECS::Manager* m_instance;
};
#endif