#ifndef BUTTON_INCLUDE
#define BUTTON_INCLUDE

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "ECS/entityClass.h"
#include <functional>

class DebugInfo;

class Button
{
public:
	Button();
	~Button();

	void init(SDL_Renderer* t_renderer, TTF_Font* t_ttf, std::string t_btnName, float t_xPos, float t_yPos);

	void setEntity(ECS::Entity& t_entity);

	void draw(SDL_Renderer* t_window);

	bool contains(int t_x, int t_y);

	void gainFocus();

	void loseFocus();

	void activate();

	void addDebugFunction(std::function<void(DebugInfo*)> t_func, DebugInfo* t_caller);
private:
	void initButtonTexture(SDL_Renderer* t_renderer);

	void initButtonText(SDL_Renderer* t_renderer, TTF_Font* t_ttf, std::string t_btnName);

	SDL_Rect m_textureRect;
	SDL_Texture* m_texture;
	SDL_Rect m_textRect;
	SDL_Texture* m_text;
	int m_sizeIncrease;
	std::function<void(DebugInfo*)> m_debugFunc;
	DebugInfo* m_debug;
};

#endif