#ifndef DEBUG_INFO_INCLUDE
#define DEBUG_INFO_INCLUDE

#include "ECS/entityClass.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include "controlSystem.h"
#include "renderSystem.h"
#include <string>
#include "button.h"

class DebugInfo
{
public:
	DebugInfo() = default;

	void init(SDL_Renderer* t_renderer);

	void handleMousePos(int t_x, int t_y);

	void activateButton();

	void updateInfo();

	void updateCurrent(ECS::Entity& t_current);

	void render();

	void addSystem(ECS::BaseSystem* t_sys) { m_systems.push_back(t_sys); }

	template<typename T>
	void toggleComp()
	{
		if (m_current)
			if (m_current->hasComponent<T>())
				m_current->removeComponent<T>();
			else
				m_current->addComponent<T>();

		updateInfo();
	}
private:
	SDL_Renderer* m_renderer;
	std::vector<ECS::BaseSystem*> m_systems;
	ECS::Manager* m_manager;
	static const int SIZE = 4;
	std::array<SDL_Texture*, SIZE> m_systemHeading;
	std::array<SDL_Texture*, SIZE> m_systemInfo;
	std::array<SDL_Rect, SIZE> m_systemRect;
	std::array<SDL_Rect, SIZE> m_systemInfoRect;
	std::array<std::string, SIZE> m_systemName;
	TTF_Font* m_font;
	SDL_Texture* m_currentEntity;
	SDL_Rect m_currentRect;
	std::vector<Button*> m_buttons;
	Button* m_activeButton;
	ECS::Entity* m_current;
};

#endif