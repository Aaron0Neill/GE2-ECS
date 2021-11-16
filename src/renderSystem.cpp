#include "renderSystem.h"

RenderSystem::RenderSystem()
{
	m_instance = ECS::Manager::getInstance();

	ECS::Signature signature;
	signature.set(m_instance->getComponentType<RenderColor>());
	signature.set(m_instance->getComponentType<Collider>());
	m_instance->setSystemSignature<RenderSystem>(signature);
}

void RenderSystem::render(SDL_Renderer* t_renderer)
{
	for (auto& e : m_entities)
	{
		SDL_Rect dim;
		RenderColor* clr = m_instance->getComponent<RenderColor>(e);
		auto b = m_instance->getComponent<Collider>(e);
		dim.x = b->position.x;
		dim.y = b->position.y;
		dim.h = b->size.h;
		dim.w = b->size.w;

		SDL_SetRenderDrawColor(t_renderer, clr->c.r, clr->c.g, clr->c.b, clr->c.a);

		SDL_RenderDrawRect(t_renderer, &dim);
	}
	highLight();
}

void RenderSystem::setActive(ECS::EntityID t_active)
{
	m_activeEntity = t_active;
}

void RenderSystem::highLight()
{
	for (auto& e : m_entities)
	{
		if (e == m_activeEntity)
		{
			SDL_Color& clr = m_instance->getComponent<RenderColor>(e)->c;
			clr.r = 255;
			clr.g = 255;
			clr.b = 255;
		}
		else
		{
			SDL_Color& clr = m_instance->getComponent<RenderColor>(e)->c;
			clr.r = 125;
			clr.g = 125;
			clr.b = 125;
		}
	}
}
