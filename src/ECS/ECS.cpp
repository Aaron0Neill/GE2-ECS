#include "ECS/ECS.h"
using namespace ECS;

Manager* Manager::m_instance{ nullptr };

Manager::Manager() :
	m_componentManager(new ComponentManager()),
	m_entityManager(new EntityManager()),
	m_systemManager(new SystemManager())
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

EntityID Manager::createEntity()
{
	return m_entityManager->createEntity();
}

//###############################

void Manager::destroyEntity(EntityID t_entity)
{
	m_componentManager->entityDestroyed(t_entity);
	m_entityManager->destroyEntity(t_entity);
	m_systemManager->entityDestroyed(t_entity);
}

//###############################