#include "game.h"
#include <iostream>

Game::Game() : 
	m_running(true)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	initWindow();

	m_ecs = ECS::Manager::getInstance();

	m_ecs->registerComponent<Input>();
	m_ecs->registerComponent<Health>();
	m_ecs->registerComponent<Position>();
	m_ecs->registerComponent<RenderInfo>();

	m_controlSystem = m_ecs->registerSystem<ControlSystem>();
	m_renderSystem = m_ecs->registerSystem<RenderSystem>();

	ECS::Entity player;
	player.addComponent<Input>();
	player.addComponent<Health>();
	player.addComponent<RenderInfo>({0,0, 100, 100, { 255,255,255,255 } });

	ECS::Entity villain;
	villain.addComponent<Health>();
	villain.addComponent<RenderInfo>({400,200, 100, 100, { 255,0,0,255 } });

	ECS::Entity cortana;
	cortana.addComponent<Health>();
	cortana.addComponent<RenderInfo>({0,0, 20, 20, { 100,100,255,255 } });

	ECS::Entity dinkyDi;
	dinkyDi.addComponent<RenderInfo>({0,0, 50, 50, { 100,255,100,255 } });
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

	m_debug.render(m_renderer);

	SDL_RenderPresent(m_renderer);
}