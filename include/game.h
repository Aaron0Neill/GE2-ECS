#ifndef GAME_INCLUDE
#define GAME_INCLUDE

#include <SDL2/SDL.h>
#include "clock.h"
#include "ECS/ECS.h"
#include "components.h"
#include "positionSystem.h"

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
    ECS::Manager m_ecs;
    std::shared_ptr<PositionSystem> m_posSystem;
};

#endif