#include "debugInfo.h"

void DebugInfo::init(SDL_Renderer* t_renderer)
{
	m_manager = ECS::Manager::getInstance();
	m_systemName[0] = "Render System";
	m_systemName[1] = "Control System";
	m_systemName[2] = "AI System";
	m_systemName[3] = "Health System";

	m_font = TTF_OpenFont("assets/calibri.ttf", 20);
	if (m_font == nullptr)
		std::cout << SDL_GetError() << "\n";

	SDL_Surface* tempSurf;
	for (int i = 0; i < SIZE; ++i)
	{
		tempSurf = TTF_RenderText_Solid(m_font, m_systemName[i].c_str(), SDL_Color{ 255,255,255,255 });
		m_systemHeading[i] = SDL_CreateTextureFromSurface(t_renderer, tempSurf);
		SDL_QueryTexture(m_systemHeading[i], NULL, NULL, &m_systemRect[i].w, &m_systemRect[i].h);

		m_systemRect[i].x = 900;
		m_systemRect[i].y = i * 100;

		if (m_systemHeading[i] == nullptr)
			std::cout << SDL_GetError() << "\n";

	}
	SDL_FreeSurface(tempSurf);

	updateInfo(t_renderer);
}


void DebugInfo::render(SDL_Renderer* t_renderer)
{
	//std::cout << "x : " << m_systemRect[1].x << ",y: " << m_systemRect[1].y << ", w: " << m_systemRect[1].w << ",h: " << m_systemRect[1].h << "\n";
	for (int i = 0; i < SIZE; ++i)
	{
		SDL_RenderCopy(t_renderer, m_systemHeading[i], NULL, &m_systemRect[i]);
		SDL_RenderCopy(t_renderer, m_systemInfo[i], NULL, &m_systemInfoRect[i]);
	}
}

void DebugInfo::updateInfo(SDL_Renderer* t_renderer)
{
	
	SDL_Surface* tempSurf;
	for (int i = 0; i < SIZE; ++i)
	{
		std::string test;

		switch (i)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}

		tempSurf = TTF_RenderText_Blended_Wrapped(m_font, "Hello This is a Test", SDL_Color{ 255,255,255,255 }, 50);
		
		m_systemInfo[i] = SDL_CreateTextureFromSurface(t_renderer, tempSurf);
		SDL_QueryTexture(m_systemInfo[i], NULL, NULL, &m_systemInfoRect[i].w, &m_systemInfoRect[i].h);

		m_systemInfoRect[i].x = 900;
		m_systemInfoRect[i].y = m_systemRect[i].y + 20;

		if (m_systemInfo[i] == nullptr)
			std::cout << SDL_GetError() << "\n";
	}
	SDL_FreeSurface(tempSurf);
}
