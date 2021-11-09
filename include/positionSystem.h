#ifndef POSITION_SYSTEM_INCLUDE
#define POSITION_SYSTEM_INCLUDE

#include "ECS/ECS.h"

class PositionSystem : public ECS::BaseSystem
{
public:
	PositionSystem() = default;

	void update();

	//void render();
private:
};

#endif 