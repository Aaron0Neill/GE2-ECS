#ifndef DEBUG_INFO_INCLUDE
#define DEBUG_INFO_INCLUDE

#include "ECS/entityClass.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <array>
#include "controlSystem.h"
#include "renderSystem.h"

class DebugInfo
{
public:
	DebugInfo(RenderSystem* t_render, ControlSystem* t_control) : m_render(t_render), m_control(t_control) {};

	void init(SDL_Renderer* t_renderer);

	void updateInfo(SDL_Renderer* t_renderer);

	void render(SDL_Renderer* t_renderer);
private:
	RenderSystem* m_render;
	ControlSystem* m_control;
	ECS::Manager* m_manager;
	static const int SIZE = 4;
	std::array<SDL_Texture*, SIZE> m_systemHeading;
	std::array<SDL_Texture*, SIZE> m_systemInfo;
	std::array<SDL_Rect, SIZE> m_systemRect;
	std::array<SDL_Rect, SIZE> m_systemInfoRect;
	std::array<std::string, SIZE> m_systemName;
	TTF_Font* m_font;
};

#endif