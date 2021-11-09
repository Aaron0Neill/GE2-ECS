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
		std::shared_ptr<T> registerSystem();

		template<typename T>
		void setSignature(Signature t_signature);

		void entityDestroyed(Entity t_entity);

		void entitySignatureChange(Entity t_entity, Signature t_signature);

	private:
		std::unordered_map<const char*, Signature> m_signatures;

		std::unordered_map<const char*, std::shared_ptr<BaseSystem>> m_systems;
	};

	//#####################################################

	template<typename T>
	inline std::shared_ptr<T> SystemManager::registerSystem()
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

	//#####################################################

	template<typename T>
	inline void SystemManager::setSignature(Signature t_signature)
	{
		const char* typeName = typeid(T).name();

		if (m_signatures.count(typeName))
		{
			m_signatures.emplace(typeName, t_signature);
		}
	}
}

#endif