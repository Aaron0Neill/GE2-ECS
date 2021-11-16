#include "game.h"
#include <iostream>

Game::Game() : 
	m_running(true),
	m_player("Player"),
	m_villain("Villain"),
	m_cortana("Cortana"),
	m_dinkiDi("Dinki Di")
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();


	m_ecs = ECS::Manager::getInstance();

	m_ecs->registerComponent<Input>();
	m_ecs->registerComponent<Health>();
	m_ecs->registerComponent<Position>();
	m_ecs->registerComponent<RenderInfo>();


	m_controlSystem = m_ecs->registerSystem<ControlSystem>();
	m_renderSystem = m_ecs->registerSystem<RenderSystem>();

	m_debug.addSystem(m_renderSystem.get());
	m_debug.addSystem(m_controlSystem.get());
	m_debug.addSystem(m_controlSystem.get());
	m_debug.addSystem(m_controlSystem.get());

	m_player.addComponent<Input>();
	m_player.addComponent<Health>();
	m_player.addCustomComponent<RenderInfo>({0,0, 100, 100, { 255,255,255,255 } });

	m_villain.addComponent<Health>();
	m_villain.addCustomComponent<RenderInfo>({400,200, 100, 100, { 255,0,0,255 } });

	m_cortana.addComponent<Health>();
	m_cortana.addComponent<Input>();
	m_cortana.addCustomComponent<RenderInfo>({0,0, 20, 20, { 100,100,255,255 } });

	m_dinkiDi.addCustomComponent<RenderInfo>({0,0, 50, 50, { 100,255,100,255 } });

	initWindow();
	m_debug.updateCurrent(m_cortana);
	m_cortana.removeComponent<Input>();
}

//###############################

void Game::run()
{
	Clock clock;
	Time lag(0U);
	const Time MS_PER_UPDATE = 1000U / 60U;
	clock.start();
	SDL_Event currentEvent;
	while (m_running)
	{
		Time dT = clock.restart();
		lag += dT;
		processEvents(currentEvent);

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}

		update(dT);
		render();
	}
}

//###############################

void Game::initWindow()
{
	m_window = SDL_CreateWindow("ECS Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 1200 / 16.0f * 9, SDL_WINDOW_INPUT_FOCUS);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

	m_debug.init(m_renderer);
}

//###############################

void Game::processEvents(SDL_Event& t_event)
{
	while (SDL_PollEvent(&t_event))
	{
		switch (t_event.type)
		{
		case SDL_QUIT:
			m_running = false;
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_MOUSEMOTION:
			m_debug.handleMousePos(t_event.button.x, t_event.button.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_debug.activateButton(m_player);
		}
	}
}

//###############################

void Game::update(Time t_dt)
{
	m_controlSystem->update(t_dt.asSeconds());
}

//###############################

void Game::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_Rect r;
	r.w = 300;
	r.x = 900;
	r.h = 1200 / 16 * 9;
	r.y = 0;
	SDL_RenderFillRect(m_renderer, &r);

	m_renderSystem->render(m_renderer);

	m_debug.render();

	SDL_RenderPresent(m_renderer);
}