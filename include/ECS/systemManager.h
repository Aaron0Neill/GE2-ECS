#ifndef SYSTEM_MANAGER_INCLUDE
#define SYSTEM_MANAGER_INCLUDE

#include "ECS/baseSystem.h"
#include "ECS/entity.h"
#include "ECS/components.h"
#include <unordered_map>
#include <typeinfo>
#include <memory>

namespace ECS
{
	class SystemManager
	{
	public:
		SystemManager() = default;
		~SystemManager() = default;

		template<typename T>
		std::shared_ptr<T> registerSystem()
		{
			const char* typeName = typeid(T).name();

			if (!m_systems.count(typeName))
			{
				auto system = std::make_shared<T>();
				m_systems.emplace(typeName, system);
				return system;
			}
			return nullptr;
		}

		template<typename T>
		void setSignature(Signature t_signature)
		{
			const char* typeName = typeid(T).name();

			if (!m_signatures.count(typeName))
			{
				m_signatures.emplace(typeName, t_signature);
			}
		}

		void entityDestroyed(EntityID t_entity)
		{
			for (auto const& pair : m_systems)
			{
				auto const& system = pair.second;

				system->m_entities.erase(t_entity);
			}
		}

		void entitySignatureChange(EntityID t_entity, Signature t_signature)
		{
			for (auto const& pair : m_systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = m_signatures[type];

				// Entity signature matches system signature - insert into set
				if ((t_signature & systemSignature) == systemSignature)
				{
					system->m_entities.insert(t_entity);
				}
				// Entity signature does not match system signature - erase from set
				else
				{
					system->m_entities.erase(t_entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, Signature> m_signatures;

		std::unordered_map<const char*, std::shared_ptr<BaseSystem>> m_systems;
	};

}

#endif