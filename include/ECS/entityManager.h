#ifndef ENTITY_MANAGER_INCLUDE
#define ENTITY_MANAGER_INCLUDE

#include "ECS/entity.h"
#include "ECS/components.h"
#include <queue>
#include <array>

namespace ECS
{
	class EntityManager
	{
	public:
		EntityManager() :
			m_livingEntityCount(0)
		{
			for (EntityID e = 0; e < MAX_ENTITIES; ++e)
				m_availableEntities.push(e);
		}

		EntityID createEntity()
		{
			if (m_livingEntityCount < MAX_ENTITIES)
			{
				EntityID id = m_availableEntities.front();
				m_availableEntities.pop();
				++m_livingEntityCount;
				return id;
			}
			return EntityID();
		}

		void destroyEntity(EntityID t_entity)
		{
			if (t_entity < MAX_ENTITIES)
			{
				m_signatures[t_entity].reset();
				m_availableEntities.push(t_entity);
				--m_livingEntityCount;
			}
		}

		void setSignature(EntityID t_entity, Signature t_signature)
		{
			if (t_entity < MAX_ENTITIES)
			{
				m_signatures[t_entity] = t_signature;
			}
		}

		Signature getSignature(EntityID t_entity)
		{
			if (t_entity < MAX_ENTITIES)
				return m_signatures[t_entity];
			return Signature();
		}

	private:
		std::queue<EntityID> m_availableEntities;

		std::array<Signature, MAX_ENTITIES> m_signatures;

		uint32_t m_livingEntityCount;
	};
}

#endif