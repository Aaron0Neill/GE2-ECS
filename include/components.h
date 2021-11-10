#ifndef COMPONENTS_INCLUDE
#define COMPONENTS_INCLUDE
#include <SDL.h>

struct Health
{
	int health;
};

struct Input
{
	float x;
	float y;
};

struct Position
{
	Position() = default;
	Position(float t_x, float t_y) : x(t_x), y(t_y) {}
	float x;
	float y;
};

struct RenderInfo
{
	RenderInfo() = default;
	RenderInfo(float t_x, float t_y, float t_w, float t_h, SDL_Color t_c) : p(t_x, t_y), w(t_w), h(t_h), c(t_c) {}
	Position p;
	float w;
	float h;
	SDL_Color c;
};

#endif