#ifndef COMPONENTS_INCLUDE
#define COMPONENTS_INCLUDE
#include <SDL.h>

struct Vec2
{
	float x;
	float y;
};

struct Box
{
	float w {50.0f};
	float h {50.0f};
};

struct AI
{
	float x;
	float y;
};

struct Input
{
	Vec2 input;
};

struct RenderColor
{
	SDL_Color c {255,255,255,255};
};

struct Collider
{
	Vec2 position;
	Box size;
};

#endif