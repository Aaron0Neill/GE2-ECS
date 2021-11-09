#ifndef ENTITY_INCLUDE
#define ENTITY_INCLUDE

#include <iostream>

namespace ECS
{
	using Entity = std::uint32_t;

	const Entity MAX_ENTITIES = 50;
}

#endif