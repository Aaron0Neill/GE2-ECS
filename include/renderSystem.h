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

	void highLight(ECS::EntityID t_active);
private:
	ECS::Manager* m_instance;
};

#endif // !RENDER_SYSTEM_INCLUDE
