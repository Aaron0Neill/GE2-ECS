#ifndef DEBUG_INFO_INCLUDE
#define DEBUG_INFO_INCLUDE

#include "ECS/entityClass.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <array>

class DebugInfo
{
public:
	DebugInfo() = default;

	void init(SDL_Renderer* t_renderer);

	void update();

	void render(SDL_Renderer* t_renderer);
private:
	void loadFont();

	ECS::Manager* m_manager;
	static const int SIZE = 2;
	std::array<SDL_Texture*, SIZE> m_systemInfo;
	std::array<SDL_Rect, SIZE> m_systemRect;
	std::array<std::string, SIZE> m_systemName;
	TTF_Font* m_font;
};

#endif