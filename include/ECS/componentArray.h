#ifndef COMPONENT_ARRAY_INCLUDE
#define COMPONENT_ARRAY_INCLUDE

#include <ECS/entity.h>
#include <unordered_map>
namespace ECS
{
	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void entityDestroyed(EntityID) = 0;
	};

	//#####################################################

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void insertData(EntityID t_entity, T t_component);

		void removeData(EntityID t_entity)
		{
			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = m_entityToIndexMap[t_entity];
			size_t indexOfLastElement = m_totalSize - 1;
			m_components[indexOfRemovedEntity] = m_components[indexOfLastElement];

			// Update map to point to moved spot
			EntityID entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
			m_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			m_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			m_entityToIndexMap.erase(t_entity);
			m_indexToEntityMap.erase(indexOfLastElement);

			--m_totalSize;
		}

		T* getData(EntityID t_entity);

		void entityDestroyed(EntityID t_entity)override;


	private:
		std::array<T, MAX_ENTITIES> m_components;

		std::unordered_map<EntityID, size_t> m_entityToIndexMap;

		std::unordered_map<size_t, EntityID> m_indexToEntityMap;

		size_t m_totalSize;
	};

	//#####################################################

	template<typename T>
	inline void ComponentArray<T>::insertData(EntityID t_entity, T t_component)
	{
		if (!m_entityToIndexMap.count(t_entity))
		{
			m_entityToIndexMap.emplace(t_entity, m_totalSize);
			m_indexToEntityMap.emplace(m_totalSize, t_entity);
			m_components[m_totalSize] = t_component;
			++m_totalSize;
		}
		else
			std::cout << "Entity already contains component\n";
	}
	 
	//#####################################################

	//template<typename T>
	//inline void ComponentArray<T>::removeData(Entity t_entity)


	//#####################################################

	template<typename T>
	inline T* ComponentArray<T>::getData(EntityID t_entity)
	{
		if (m_entityToIndexMap.count(t_entity))
			return &m_components[m_entityToIndexMap.at(t_entity)];
		else
			std::cout << "Entity doesnt contain this data\n";
		return nullptr;
	}

	//#####################################################

	template<typename T>
	inline void ComponentArray<T>::entityDestroyed(EntityID t_entity)
	{
		if (m_entityToIndexMap.count(t_entity))
			removeData(t_entity);
		else
			std::cout << "Entity Not found\n";
	}

}
#endif