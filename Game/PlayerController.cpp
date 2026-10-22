#include "PlayerController.h"
#include <Engine.h>
#include <Components/PhysicsComponent.h>
#include <Components/SpriteAnimationRendererComponent.h>



void PlayerController::Start()
{
	Actor::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimationRendererComponent>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{
	float dir = 0.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1.0f;


	nu::Vector2 vel = m_physicsComponent->GetVelocity();

	if (dir != 0.0f) {
		vel.x = dir * 1000.0f;
	}

	m_physicsComponent->SetVelocity(vel);
	Actor::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* actor)
{
}

void PlayerController::Read(const nu::json::value_t& value)
{
}
