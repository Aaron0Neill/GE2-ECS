#include "renderSystem.h"

RenderSystem::RenderSystem()
{
	m_instance = ECS::Manager::getInstance();

	ECS::Signature signature;
	signature.set(m_instance->getComponentType<Position>());
	signature.set(m_instance->getComponentType<Box>());
	m_instance->setSystemSignature<RenderSystem>(signature);
}

void RenderSystem::render(SDL_Renderer* t_renderer)
{
	for (auto& e : m_entities)
	{
		SDL_Rect dim;
		Position& p = m_instance->getComponent<Position>(e);
		Box& b = m_instance->getComponent<Box>(e);
		dim.x = p.x;
		dim.y = p.y;
		dim.h = b.h;
		dim.w = b.w;

		SDL_RenderDrawRect(t_renderer, &dim);
	}
}
