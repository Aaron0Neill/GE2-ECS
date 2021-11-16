#include "debugInfo.h"

void DebugInfo::init(SDL_Renderer* t_renderer)
{
	m_manager = ECS::Manager::getInstance();
	m_renderer = t_renderer;
	m_systemName[0] = "Render System";
	m_systemName[1] = "Control System";
	m_systemName[2] = "AI System";
	m_systemName[3] = "Collision System";

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

	updateInfo();

	tempSurf = TTF_RenderText_Solid(m_font, "Current: ", SDL_Color{255,255,255,255});
	m_currentEntity = SDL_CreateTextureFromSurface(t_renderer, tempSurf);
	SDL_QueryTexture(m_currentEntity, NULL, NULL, &m_currentRect.w, &m_currentRect.h);

	m_currentRect.x = 900;
	m_currentRect.y = 400;

	SDL_FreeSurface(tempSurf);

	m_buttons.push_back(new Button());
	m_buttons.push_back(new Button());
	m_buttons.push_back(new Button());
	m_buttons.push_back(new Button());

	m_buttons[0]->init(m_renderer, m_font, "render", 910, 450);
	m_buttons[1]->init(m_renderer, m_font, "Control", 1200 - 138, 450);
	m_buttons[2]->init(m_renderer, m_font, "AI", 910, 450 + 74);
	m_buttons[3]->init(m_renderer, m_font, "Collider", 1200 - 138, 450 + 74);

	m_buttons[0]->addDebugFunction(&DebugInfo::toggleComp<RenderColor>, this);
	m_buttons[1]->addDebugFunction(&DebugInfo::toggleComp<Input>, this);
	m_buttons[2]->addDebugFunction(&DebugInfo::toggleComp<AI>, this);
	m_buttons[3]->addDebugFunction(&DebugInfo::toggleComp<Collider>, this);
}

//********************************************************

void DebugInfo::handleMousePos(int t_x, int t_y)
{
	for (auto& btn : m_buttons)
	{
		if (btn->contains(t_x, t_y))
		{
			if (m_activeButton != btn)
			{
				if (m_activeButton != nullptr)
					m_activeButton->loseFocus();
				m_activeButton = btn;
				m_activeButton->gainFocus();
				break;
			}
		}
		else if (m_activeButton == btn)
			if (m_activeButton != nullptr)
			{
				m_activeButton->loseFocus();
				m_activeButton = nullptr;
			}
	}
}

//********************************************************

void DebugInfo::activateButton()
{
	if (m_activeButton)
		m_activeButton->activate();
}

//********************************************************

void DebugInfo::render()
{
	//std::cout << "x : " << m_systemRect[1].x << ",y: " << m_systemRect[1].y << ", w: " << m_systemRect[1].w << ",h: " << m_systemRect[1].h << "\n";
	for (int i = 0; i < SIZE; ++i)
	{
		SDL_RenderCopy(m_renderer, m_systemHeading[i], NULL, &m_systemRect[i]);
		SDL_RenderCopy(m_renderer, m_systemInfo[i], NULL, &m_systemInfoRect[i]);
	}
	SDL_RenderCopy(m_renderer, m_currentEntity, NULL, &m_currentRect);
	for (auto& btn : m_buttons)
		btn->draw(m_renderer);
}

//********************************************************

void DebugInfo::updateInfo()
{	
	SDL_Surface* tempSurf;

	for (int i = 0; i < SIZE; ++i)
	{
		std::string test = "";

		for (auto& e : m_systems[i]->m_entities)
		{
			test += m_manager->getName(e);
			if (e != *m_systems[i]->m_entities.rbegin())
				test += ", ";
		}

		tempSurf = TTF_RenderText_Blended_Wrapped(m_font, test.c_str(), SDL_Color{255,255,255,255}, 300);
		
		m_systemInfo[i] = SDL_CreateTextureFromSurface(m_renderer, tempSurf);
		SDL_QueryTexture(m_systemInfo[i], NULL, NULL, &m_systemInfoRect[i].w, &m_systemInfoRect[i].h);

		m_systemInfoRect[i].x = 900;
		m_systemInfoRect[i].y = m_systemRect[i].y + 20;

		if (m_systemInfo[i] == nullptr)
			std::cout << SDL_GetError() << "\n";
	}
	SDL_FreeSurface(tempSurf);
}

//********************************************************

void DebugInfo::updateCurrent(ECS::Entity& t_current)
{
	m_current = &t_current;
	SDL_Surface* tempSurf;
	std::string current = "Current: ";
	current += m_manager->getName(t_current);
	tempSurf = TTF_RenderText_Solid(m_font, current.c_str(), SDL_Color{ 255,255,255,255 });
	m_currentEntity = SDL_CreateTextureFromSurface(m_renderer, tempSurf);
	SDL_QueryTexture(m_currentEntity, NULL, NULL, &m_currentRect.w, &m_currentRect.h);
	SDL_FreeSurface(tempSurf);
}
