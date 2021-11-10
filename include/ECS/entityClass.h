#ifndef ENTITY_CLASS_INCLUDE
#define ENTITY_CLASS_INCLUDE

#include "ECS/ECS.h"
#include <string>

namespace ECS {

	class Entity
	{
	public:
		Entity()
		{
			m_manager = Manager::getInstance();

			m_id = m_manager->createEntity();
		}

		template<typename T>
		void addComponent(T t_component = T())
		{
			m_manager->addComponent(m_id, t_component);
		}

		template<typename T>
		void removeComponent(T t_component)
		{
			m_manager->removeComponent<T>(m_id);
		}

		operator EntityID() { return m_id; }

	private:
		Manager* m_manager;
		EntityID m_id;
	};
}

#endif