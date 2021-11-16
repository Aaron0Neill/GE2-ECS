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
	signature.set(m_instance->getComponentType<Collider>());
	m_instance->setSystemSignature<ControlSystem>(signature);
}

//###############################

void ControlSystem::update(float t_dt)
{
	const Uint8* keystates = SDL_GetKeyboardState(0);

	for (auto e : m_entities)
	{
		Input* input = m_instance->getComponent<Input>(e);
		input->input.x += keystates[SDL_SCANCODE_A] * -m_changeSpeed * t_dt * 2;
		input->input.x += keystates[SDL_SCANCODE_D] * m_changeSpeed * t_dt * 2;
			 
		input->input.y += keystates[SDL_SCANCODE_S] * m_changeSpeed * t_dt * 2;
		input->input.y += keystates[SDL_SCANCODE_W] * -m_changeSpeed * t_dt * 2;

		if (powf(input->input.x, 2) > 1)
			input->input.x /= std::abs(input->input.x);
		if (powf(input->input.y, 2) > 1)
			input->input.y /= std::abs(input->input.y);

		input->input.x -= input->input.x * m_decelerate * t_dt;
		input->input.y -= input->input.y * m_decelerate * t_dt;

		if (input->input.x < 0.01f && input->input.x > -0.01f)
			input->input.x = 0;
		if (input->input.y < 0.01f && input->input.y > -0.01f)
			input->input.y = 0;

		Vec2& pos = m_instance->getComponent<Collider>(e)->position;

		pos.x += input->input.x * t_dt * m_speed;
		pos.y += input->input.y * t_dt * m_speed;

	}
}