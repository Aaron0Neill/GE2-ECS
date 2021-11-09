#include "game.h"
#include <iostream>

Game::Game() : 
	m_running(true),
	t(true)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	initWindow();

	m_ecs = ECS::Manager::getInstance();

	m_ecs->registerComponent<Input>();
	m_ecs->registerComponent<Health>();
	m_ecs->registerComponent<Position>();
	m_ecs->registerComponent<Box>();

	m_controlSystem = m_ecs->registerSystem<ControlSystem>().get();
	m_renderSystem = m_ecs->registerSystem<RenderSystem>().get();

	e = m_ecs->createEntity();
	m_ecs->addComponent(e, Input());
	m_ecs->addComponent(e, Position());
	m_ecs->addComponent(e, Box(100,100));
	m_ecs->removeComponent<Position>(e);
	m_entities.push_back(e);
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
			if (t_event.key.keysym.sym == 'f')
			{
				std::cout << "F\n";
				if (t)
				{
					m_ecs->removeComponent<Position>(e);
					t = false;	
				}
				else if (!t)
				{
					std::cout << "not T\n";
					m_ecs->addComponent(e, Position());
					t = true;
				}
			}
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

	SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

	m_renderSystem->render(m_renderer);

	SDL_RenderPresent(m_renderer);
}