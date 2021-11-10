#ifndef CONTROL_SYSTEM_INCLUDE
#define CONTROL_SYSTEM_INCLUDE

#include "ECS/ECS.h"
#include "components.h"
#include <SDL.h>

class ControlSystem : public ECS::BaseSystem
{
public:
	ControlSystem();

	void update(float t_dt);
private:
	ECS::Manager* m_instance;
	float m_decelerate;
	float m_changeSpeed;
	float m_speed;
};

#endif 