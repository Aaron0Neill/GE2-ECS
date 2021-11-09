#include "ECS/entityManager.h"
using namespace ECS;

EntityManager::EntityManager() : 
	m_livingEntityCount(0)
{
	for (Entity e = 0; e < MAX_ENTITIES; ++e)
		m_availableEntities.push(e);
}

//###########################################################################

Entity EntityManager::createEntity()
{
	if (m_livingEntityCount < MAX_ENTITIES)
	{
		Entity id = m_availableEntities.front();
		m_availableEntities.pop();
		++m_livingEntityCount;
		return id;
	}
	return Entity();
}

//###########################################################################

void EntityManager::destroyEntity(Entity t_entity)
{
	if (t_entity < MAX_ENTITIES)
	{
		m_signatures[t_entity].reset();
		m_availableEntities.push(t_entity);
		--m_livingEntityCount;
	}
}

//###########################################################################

void EntityManager::setSignature(Entity t_entity, Signature t_signature)
{
	if (t_entity < MAX_ENTITIES)
	{
		m_signatures[t_entity] = t_signature;
	}
}

//###########################################################################

Signature EntityManager::getSignature(Entity t_entity)
{
	if (t_entity < MAX_ENTITIES)
		return m_signatures[t_entity];
	return Signature();
}
