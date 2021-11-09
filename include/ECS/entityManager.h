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

		Entity createEntity();

		void destroyEntity(Entity t_entity);

		void setSignature(Entity t_entity, Signature t_signature);

		Signature getSignature(Entity t_entity);

	private:
		std::queue<Entity> m_availableEntities;

		std::array<Signature, MAX_ENTITIES> m_signatures;

		uint32_t m_livingEntityCount;
	};
}

#endif