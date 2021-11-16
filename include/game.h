#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SDL.h>
#include "clock.h"
#include "ECS/EntityClass.h"
#include "components.h"
#include "controlSystem.h"
#include "renderSystem.h"
#include <vector>
#include "debugInfo.h"

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
    std::shared_ptr<ControlSystem> m_controlSystem;
    std::shared_ptr<RenderSystem> m_renderSystem;
    DebugInfo m_debug;
    ECS::Entity m_player, m_villain, m_cortana, m_dinkiDi;
};

#endif