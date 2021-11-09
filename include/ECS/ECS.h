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
		Manager();

		Entity createEntity();

		void destroyEntity(Entity t_entity);

		template<typename T>
		void registerComponent();

		template<typename T>
		void addComponent(Entity t_entity, T t_component);

		template<typename T>
		void removeComponent(Entity);

		template<typename T>
		T& getComponent(Entity t_entity);

		template<typename T>
		ComponentType getComponentType();

		template<typename T>
		std::shared_ptr<T> registerSystem();

		template<typename T>
		void setSystemSignature(Signature);

	private:
		std::unique_ptr<ComponentManager> m_componentManager;
		std::unique_ptr<EntityManager> m_entityManager;
		std::unique_ptr<SystemManager> m_systemManager;
	};

	//##############################################

	template<typename T>
	inline void Manager::registerComponent()
	{
		m_componentManager->registerComponent<T>();
	}

	//##############################################

	template<typename T>
	inline void Manager::addComponent(Entity t_entity, T t_component)
	{
		m_componentManager->addComponent<T>(t_entity, t_component);
	}

	//##############################################

	template<typename T>
	inline void Manager::removeComponent(Entity t_entity)
	{
		m_componentManager->removeComponent<T>(t_entity);

		Signature signature = m_entityManager->getSignature(t_entity);
		signature.set(m_componentManager->getComponent<T>(), false);
		m_entityManager->setSignature(t_entity, signature);

		m_systemManager->entitySignatureChange(t_entity, signature);
	}

	//##############################################

	template<typename T>
	inline T& Manager::getComponent(Entity t_entity)
	{
		return m_componentManager->getComponent<T>(t_entity);
	}

	//##############################################

	template<typename T>
	inline ComponentType Manager::getComponentType()
	{
		return m_componentManager->getComponent<T>();
	}

	//##############################################

	template<typename T>
	inline std::shared_ptr<T> Manager::registerSystem()
	{
		return m_systemManager->registerSystem<T>();
	}
}
#endif