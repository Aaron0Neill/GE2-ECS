#ifndef ECS_INCLUDE
#define ECS_INCLUDE

#include "componentManager.h"
#include "entityManager.h"
#include "systemManager.h"

namespace ECS
{
	class Manager
	{
	public:
		
		inline static Manager* getInstance()
		{
			static Manager m_instance;

			return &m_instance;
		}
		Manager(Manager const&)=delete;
		void operator=(Manager const&)=delete;

		inline void setName(const char* t_name, EntityID t_id)
		{
			m_naming[t_id] = t_name;
		}

		inline const char* getName(EntityID t_id)
		{
			return m_naming[t_id];
		}

		inline EntityID createEntity()
		{
			return m_entityManager->createEntity();
		}

		inline void destroyEntity(EntityID& t_entity)
		{
			m_componentManager->entityDestroyed(t_entity);
			m_entityManager->destroyEntity(t_entity);
			m_systemManager->entityDestroyed(t_entity);
		}

		template<typename T>
		inline void registerComponent()
		{
			m_componentManager->registerComponent<T>();
		}

		template<typename T>
		inline void addComponent(EntityID& t_entity, T t_component)
		{
			m_componentManager->addComponent<T>(t_entity, t_component);

			auto signature = m_entityManager->getSignature(t_entity);
			signature.set(m_componentManager->getComponentType<T>(), true);
			m_entityManager->setSignature(t_entity, signature);

			m_systemManager->entitySignatureChange(t_entity, signature);
		}

		template<typename T>
		inline void removeComponent(EntityID t_entity)
		{
			m_componentManager->removeComponent<T>(t_entity);

			Signature signature = m_entityManager->getSignature(t_entity);
			signature.set(m_componentManager->getComponentType<T>(), false);
			m_entityManager->setSignature(t_entity, signature);

			m_systemManager->entitySignatureChange(t_entity, signature);
		}

		template<typename T>
		inline T* getComponent(EntityID t_entity)
		{
			return m_componentManager->getComponent<T>(t_entity);
		}

		template<typename T>
		inline ComponentType getComponentType()
		{
			return m_componentManager->getComponentType<T>();
		}

		template<typename T>
		inline std::shared_ptr<T> registerSystem()
		{
			return m_systemManager->registerSystem<T>();
		}

		template<typename T>
		inline void setSystemSignature(Signature t_signature)
		{
			m_systemManager->setSignature<T>(t_signature);
		}

	private:
		Manager() :
			m_componentManager(new ComponentManager()),
			m_entityManager(new EntityManager()),
			m_systemManager(new SystemManager())
		{
		}
		ComponentManager* m_componentManager;
		EntityManager* m_entityManager;
		SystemManager* m_systemManager;
		std::unordered_map<EntityID, const char*> m_naming;
	};
}
#endif