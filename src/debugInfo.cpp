#include "debugInfo.h"

void DebugInfo::init(SDL_Renderer* t_renderer)
{
	m_manager = ECS::Manager::getInstance();
	m_systemName[0] = "RenderSystem";
	m_systemName[1] = "ControlSystem";

	m_font = TTF_OpenFont("assets/calibri.ttf", 20);
	if (m_font == nullptr)
		std::cout << SDL_GetError() << "\n";

	for (int i = 0; i < SIZE; ++i)
	{
		SDL_Surface* tempSurf = TTF_RenderText_Solid(m_font, m_systemName[i].c_str(), SDL_Color{ 255,255,255,255 });

		m_systemInfo[i] = SDL_CreateTextureFromSurface(t_renderer, tempSurf);
		SDL_QueryTexture(m_systemInfo[i], NULL, NULL, &m_systemRect[i].w, &m_systemRect[i].h);

		m_systemRect[i].x = 900;
		m_systemRect[i].y = 100;

		if (m_systemInfo[i] == nullptr)
			std::cout << SDL_GetError() << "\n";

		SDL_FreeSurface(tempSurf);
	}

	m_systemRect[1].y += 200;
}

void DebugInfo::update()
{
}

void DebugInfo::render(SDL_Renderer* t_renderer)
{
	//std::cout << "x : " << m_systemRect[1].x << ",y: " << m_systemRect[1].y << ", w: " << m_systemRect[1].w << ",h: " << m_systemRect[1].h << "\n";
	for (int i = 0; i < SIZE; ++i)
	{
		SDL_RenderCopy(t_renderer, m_systemInfo[i], NULL, &m_systemRect[i]);
	}
}

void DebugInfo::loadFont()
{
}
