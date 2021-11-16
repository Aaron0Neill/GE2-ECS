#include "collisionSystem.h"

CollisionSystem::CollisionSystem()
{
	m_instance = ECS::Manager::getInstance();

	ECS::Signature signature;
	signature.set(m_instance->getComponentType<Collider>());
	signature.set(m_instance->getComponentType<RenderColor>());
	m_instance->setSystemSignature<CollisionSystem>(signature);
}

void CollisionSystem::update()
{
	for (auto& self : m_entities)
		for (auto& other : m_entities)
			if (other != self)
				if (checkCollision(self, other))
				{
					SDL_Color& selfClr = m_instance->getComponent<RenderColor>(self)->c;
					selfClr.r = 255;
					selfClr.b = 0;
					selfClr.g = 0;
					SDL_Color& otherClr = m_instance->getComponent<RenderColor>(other)->c;
					otherClr.r = 0;
					otherClr.b = 0;
					otherClr.g = 255;
				}
}

bool CollisionSystem::checkCollision(ECS::EntityID t_self, ECS::EntityID t_other)
{
	auto c = m_instance->getComponent<Collider>(t_self);
	auto c2 = m_instance->getComponent<Collider>(t_other);
	return (c->position.x < c2->position.x + c2->size.w &&
			c->position.x + c->size.w > c2->position.x &&
			c->position.y < c2->position.y + c2->size.h &&
			c->position.y + c->size.h > c2->position.y);
}
