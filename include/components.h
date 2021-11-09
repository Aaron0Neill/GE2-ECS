#ifndef COMPONENTS_INCLUDE
#define COMPONENTS_INCLUDE

struct Health
{
	int health;
};

struct Input
{
	float x;
	float y;
};

struct Box
{
	Box() = default;
	Box(float t_w, float t_h) : w(t_w), h(t_h) {}
	float w;
	float h;
};

struct Position
{
	float x;
	float y;
};

#endif