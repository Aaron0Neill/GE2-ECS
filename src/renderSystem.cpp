#include "renderSystem.h"

RenderSystem::RenderSystem()
{
	m_instance = ECS::Manager::getInstance();

	ECS::Signature signature;
	signature.set(m_instance->getComponentType<RenderInfo>());
	m_instance->setSystemSignature<RenderSystem>(signature);
}

void RenderSystem::render(SDL_Renderer* t_renderer)
{
	for (auto& e : m_entities)
	{
		SDL_Rect dim;
		RenderInfo* b = m_instance->getComponent<RenderInfo>(e);
		dim.x = b->p.x;
		dim.y = b->p.y;
		dim.h = b->h;
		dim.w = b->w;

		SDL_SetRenderDrawColor(t_renderer, b->c.r, b->c.g, b->c.b, b->c.a);

		SDL_RenderDrawRect(t_renderer, &dim);
	}
}
