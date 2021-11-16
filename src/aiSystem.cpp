#include "aiSystem.h"

aiSystem::aiSystem()
{
	m_instance = ECS::Manager::getInstance();

	ECS::Signature signature;
	signature.set(m_instance->getComponentType<Collider>());
	signature.set(m_instance->getComponentType<AI>());
	m_instance->setSystemSignature<aiSystem>(signature);
}

//************************************

void aiSystem::update(float t_dt)
{
	for (auto& e : m_entities)
	{
		Vec2& p = m_instance->getComponent<Collider>(e)->position;
		auto target = m_instance->getComponent<AI>(e);
		float diffX = target->x - p.x;
		float diffY = target->y - p.y;
		float mag = sqrt(diffX * diffX + diffY * diffY);
		diffX /= (mag != 0) ? mag : 1;
		diffY /= (mag != 0) ? mag : 1;

		p.x += diffX * t_dt * 2;
		p.y += diffY * t_dt * 2;
	}
}
