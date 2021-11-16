#ifndef RENDER_SYSTEM_INCLUDE
#define RENDER_SYSTEM_INCLUDE

#include "ECS/ECS.h"
#include "components.h"
#include <SDL.h>

class RenderSystem : public ECS::BaseSystem
{
public:
	RenderSystem();

	void render(SDL_Renderer* m_window);

	void setActive(ECS::EntityID t_active);
private:
	void highLight();
	ECS::Manager* m_instance;
	ECS::EntityID m_activeEntity;
};

#endif // !RENDER_SYSTEM_INCLUDE
