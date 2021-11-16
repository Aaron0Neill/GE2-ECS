#ifndef AI_SYSTEM_INCLUDE
#define AI_SYSTEM_INCLUDE

#include "ECS/ECS.h"
#include "components.h"
#include <SDL.h>

class aiSystem : public ECS::BaseSystem
{
public:
	aiSystem();

	void update(float t_dt);
private:
	ECS::Manager* m_instance;

};


#endif