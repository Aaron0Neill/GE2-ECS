#ifndef COMPONENETS_INCLUDE
#define COMPONENETS_INCLUDE

#include <bitset>
namespace ECS
{
	using ComponentType = std::uint8_t;

	const ComponentType MAX_COMPONENTS = 16;

	using Signature = std::bitset<MAX_COMPONENTS>;
}

#endif