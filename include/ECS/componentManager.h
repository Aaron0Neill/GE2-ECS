#ifndef COMPONENT_MANAGER_INCLUDE
#define COMPONENT_MANAGER_INCLUDE

#include "ECS/componentArray.h"
#include "components.h"
#include <typeinfo>
#include <memory>

namespace ECS
{
	class ComponentManager
	{
	public:

		template<typename T>
		void registerComponent();

		template<typename T>
		ComponentType getComponentType();

		template<typename T>
		void addComponent(Entity t_entity, T t_component);

		template<typename T>
		void removeComponent(Entity t_entity);

		template<typename T>
		T& getComponent(Entity t_entity);

		void entityDestroyed(Entity t_entity)
		{
			for (auto const& pair : m_componentArrays)
			{
				auto const& component = pair.second;

				component->entityDestroyed(t_entity);
			}
		}

	private:
		std::unordered_map<const char*, ComponentType> m_componentType;

		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;

		ComponentType m_nextComponentType{};

		template<typename T>
		std::shared_ptr<ComponentArray<T>> getComponentArray()
		{
			const char* typeName = typeid(T).name();

			if (m_componentType.count(typeName))
				return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
			else
				std::cout << "Component has not been registered\n";

			return nullptr;
		}
	};

	//#####################################################

	template<typename T>
	inline void ComponentManager::registerComponent()
	{
		const char* typeName = typeid(T).name();

		if (!m_componentType.count(typeName))
		{
			m_componentType.emplace(typeName, m_nextComponentType);

			m_componentArrays.emplace(typeName, std::make_shared<ComponentArray<T>>());

			m_nextComponentType++;
		}
		else
			std::cout << "Component is already registered\n";
	}

	//#####################################################

	template<typename T>
	inline ComponentType ComponentManager::getComponentType()
	{
		const char* typeName = typeid(T).name();

		if (m_componentType.count(typeName))
			return m_componentType.at(typeName);
		else
			std::cout << "Component doesn't exist\n";
		return ComponentType();
	}

	//#####################################################

	template<typename T>
	inline void ComponentManager::addComponent(Entity t_entity, T t_component)
	{
		getComponentArray<T>()->insertData(t_entity, t_component);
	}

	//#####################################################

	template<typename T>
	inline void ComponentManager::removeComponent(Entity t_entity)
	{
		getComponentArray<T>()->removeData(t_entity);
	}

	//#####################################################

	template<typename T>
	inline T& ComponentManager::getComponent(Entity t_entity)
	{
		getComponentArray<T>()->getData(t_entity);
	}
}

#endif