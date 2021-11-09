#include "ECS/systemManager.h"
using namespace ECS;

void SystemManager::entityDestroyed(Entity t_entity)
{
	for (auto const& pair : m_systems)
	{
		auto const& system = pair.second;

		system->m_entities.erase(t_entity);
	}
}

//#####################################################

void SystemManager::entitySignatureChange(Entity t_entity, Signature t_signature)
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
