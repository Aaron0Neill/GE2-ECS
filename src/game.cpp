#include "game.h"
#include <iostream>

Game::Game() : 
	m_running(true)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	initWindow();
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
		}
	}
}

//###############################

void Game::update(Time t_dt)
{
}

//###############################

void Game::render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);

	SDL_RenderPresent(m_renderer);
}