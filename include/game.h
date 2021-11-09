#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SDL.h>
#include "clock.h"
#include "ECS/ECS.h"
#include "components.h"
#include "controlSystem.h"
#include "renderSystem.h"
#include <vector>

class Game
{
public:
    Game();

    void run();

private:

    void initWindow();
    void processEvents(SDL_Event& t_event);
    void update(Time t_dt);
    void render();
 
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    bool m_running;
    ECS::Manager* m_ecs;
    ControlSystem* m_controlSystem;
    RenderSystem* m_renderSystem;
    std::vector<ECS::Entity> m_entities;
    ECS::Entity e;
    bool t;
};

#endif