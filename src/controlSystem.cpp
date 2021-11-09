#include "controlSystem.h"
#include <iostream>

ControlSystem::ControlSystem() : 
	m_changeSpeed(0.6f),
	m_decelerate(1.0f),
	m_speed(20.0f)
{
	m_instance = ECS::Manager::getInstance();

	ECS::Signature signature;
	signature.set(m_instance->getComponentType<Input>());
	signature.set(m_instance->getComponentType<Position>());
	m_instance->setSystemSignature<ControlSystem>(signature);
}

//###############################

void ControlSystem::update(float t_dt)
{
	const Uint8* keystates = SDL_GetKeyboardState(0);

	for (auto e : m_entities)
	{
		Input& input = m_instance->getComponent<Input>(e);
		input.x += keystates[SDL_SCANCODE_A] * -m_changeSpeed * t_dt * 2;
		input.x += keystates[SDL_SCANCODE_D] * m_changeSpeed * t_dt * 2;

		input.y += keystates[SDL_SCANCODE_S] * m_changeSpeed * t_dt * 2;
		input.y += keystates[SDL_SCANCODE_W] * -m_changeSpeed * t_dt * 2;

		if (powf(input.x, 2) > 1)
			input.x /= std::abs(input.x);
		if (powf(input.y, 2) > 1)
			input.y /= std::abs(input.y);

		input.x -= input.x * m_decelerate * t_dt;
		input.y -= input.y * m_decelerate * t_dt;

		if (input.x < 0.01f && input.x > -0.01f)
			input.x = 0;
		if (input.y < 0.01f && input.y > -0.01f)
			input.y = 0;

		Position& pos = m_instance->getComponent<Position>(e);

		pos.x += input.x * t_dt * m_speed;
		pos.y += input.y * t_dt * m_speed;
	}
}