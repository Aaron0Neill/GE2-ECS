#include "ECS/ECS.h"
using namespace ECS;

Manager::Manager() :
	m_componentManager(std::make_unique<ComponentManager>()),
	m_entityManager(std::make_unique<EntityManager>()),
	m_systemManager(std::make_unique<SystemManager>())
{
}

Entity Manager::createEntity()
{
	return m_entityManager->createEntity();
}

void Manager::destroyEntity(Entity t_entity)
{
	m_componentManager->entityDestroyed(t_entity);
	m_entityManager->destroyEntity(t_entity);
	m_systemManager->entityDestroyed(t_entity);
}

template<typename T>
void Manager::setSystemSignature(Signature t_signature)
{
	m_systemManager->setSignature<T>(t_signature);
}