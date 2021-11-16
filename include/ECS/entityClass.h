#ifndef ENTITY_CLASS_INCLUDE
#define ENTITY_CLASS_INCLUDE

#include "ECS/ECS.h"
#include <string>

namespace ECS {

	class Entity
	{
	public:
		Entity(const char* t_name = nullptr)
		{
			std::string name;
			m_manager = Manager::getInstance();

			m_id = m_manager->createEntity();

			if (t_name == nullptr)
				name = "Entity " + std::to_string(m_id);

			m_manager->setName(((t_name == nullptr) ? name.c_str():
						t_name), m_id);
		}

		template<typename T>
		void addComponent()
		{
			m_manager->addComponent(m_id, T());
		}

		template<typename T>
		void addCustomComponent(T t_component)
		{
			m_manager->addComponent(m_id, t_component);
		}

		template<typename T>
		void removeComponent()
		{
			m_manager->removeComponent<T>(m_id);
		}

		void setName(const char* t_name)
		{
			m_manager->setName(t_name, m_id);
		}

		template<typename T>
		bool hasComponent()
		{
			return (m_manager->getComponent<T>(m_id) != nullptr);
		}

		operator EntityID() { return m_id; }

	private:
		Manager* m_manager;
		EntityID m_id;
	};
}

#endif