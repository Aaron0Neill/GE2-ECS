#include "ECS/ECS.h"
using namespace ECS;

Manager* Manager::m_instance{ nullptr };

Manager::Manager() :
	m_componentManager(std::make_unique<ComponentManager>()),
	m_entityManager(std::make_unique<EntityManager>()),
	m_systemManager(std::make_unique<SystemManager>())
{
}

//###############################

Manager* ECS::Manager::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new Manager();

	return m_instance;
}

//###############################

Entity Manager::createEntity()
{
	return m_entityManager->createEntity();
}

//###############################

void Manager::destroyEntity(Entity t_entity)
{
	m_componentManager->entityDestroyed(t_entity);
	m_entityManager->destroyEntity(t_entity);
	m_systemManager->entityDestroyed(t_entity);
}

//###############################