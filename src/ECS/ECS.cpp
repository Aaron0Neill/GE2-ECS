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

void ECS::Manager::setName(const char* t_name, EntityID t_id)
{
	m_naming[t_id] = t_name;
}

//###############################

const char* ECS::Manager::getName(EntityID t_id)
{
	return m_naming[t_id];
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