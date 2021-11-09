#ifndef BASE_SYSTEM_INCLUDE
#define BASE_SYSTEM_INCLUDE

#include <set>
#include "ECS/entity.h"
namespace ECS
{
	class BaseSystem
	{
	public:
		std::set<Entity> m_entities;
	};
}
#endif