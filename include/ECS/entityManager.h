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
		EntityManager();

		EntityID createEntity();

		void destroyEntity(EntityID t_entity);

		void setSignature(EntityID t_entity, Signature t_signature);

		Signature getSignature(EntityID t_entity);

	private:
		std::queue<EntityID> m_availableEntities;

		std::array<Signature, MAX_ENTITIES> m_signatures;

		uint32_t m_livingEntityCount;
	};
}

#endif