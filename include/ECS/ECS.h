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
		
		static Manager* getInstance();

		Manager(Manager const&) = delete;
		void operator=(Manager const&)= delete;

		void setName(const char* t_name, EntityID t_id);

		const char* getName(EntityID t_id);

		EntityID createEntity();

		void destroyEntity(EntityID);

		template<typename T>
		void registerComponent();

		template<typename T>
		void addComponent(EntityID, T);

		template<typename T>
		void removeComponent(EntityID);

		template<typename T>
		T* getComponent(EntityID);

		template<typename T>
		ComponentType getComponentType();

		template<typename T>
		std::shared_ptr<T> registerSystem();

		template<typename T>
		void setSystemSignature(Signature);

	private:
		Manager();
		static Manager* m_instance;
		ComponentManager* m_componentManager;
		EntityManager* m_entityManager;
		SystemManager* m_systemManager;
		std::unordered_map<EntityID, const char*> m_naming;
	};

	//##############################################

	template<typename T>
	inline void Manager::registerComponent()
	{
		m_componentManager->registerComponent<T>();
	}

	//##############################################

	template<typename T>
	inline void Manager::addComponent(EntityID t_entity, T t_component)
	{
		m_componentManager->addComponent<T>(t_entity, t_component);

		auto signature = m_entityManager->getSignature(t_entity);
		signature.set(m_componentManager->getComponentType<T>(), true);
		m_entityManager->setSignature(t_entity, signature);

		m_systemManager->entitySignatureChange(t_entity, signature);
	}

	//##############################################

	template<typename T>
	inline void Manager::removeComponent(EntityID t_entity)
	{
		m_componentManager->removeComponent<T>(t_entity);

		Signature signature = m_entityManager->getSignature(t_entity);
		signature.set(m_componentManager->getComponentType<T>(), false);
		m_entityManager->setSignature(t_entity, signature);

		m_systemManager->entitySignatureChange(t_entity, signature);
	}

	//##############################################

	template<typename T>
	inline T* Manager::getComponent(EntityID t_entity)
	{
		return m_componentManager->getComponent<T>(t_entity);
	}

	//##############################################

	template<typename T>
	inline ComponentType Manager::getComponentType()
	{
		return m_componentManager->getComponentType<T>();
	}

	//##############################################

	template<typename T>
	inline std::shared_ptr<T> Manager::registerSystem()
	{
		return m_systemManager->registerSystem<T>();
	}

	template<typename T>
	inline void Manager::setSystemSignature(Signature t_signature)
	{
		m_systemManager->setSignature<T>(t_signature);
	}
}
#endif