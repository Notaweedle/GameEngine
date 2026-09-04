#include "PlayerController.h"
#include <Engine.h>
#include <Components/PhysicsComponent.h>
#include <Components/SpriteAnimatorRendererComponet.h>
#include <Core/Factory.h>
#include <Serialization/Json.h>

FACTORY_REGISTER(PlayerController)

void PlayerController::Start()
{
	Actor::Start();

	m_physicsComponent = GetComponent<nu::PhysicsComponent>();
	assert(m_physicsComponent);
	m_rendererComponent = GetComponent<nu::SpriteAnimatorRendererComponet>();
	assert(m_rendererComponent);
}

void PlayerController::Update(float dt)
{
	// camera follows the player even when dead / attacking
	nu::Engine::Get().GetRenderer().setCamera(m_physicsComponent->GetPosition());

	// dead: hold the death animation, no movement
	if (m_dead)
	{
		m_physicsComponent->SetVelocity(nu::Vector2{ 0.0f, 0.0f });
		m_rendererComponent->Play("death");
		Actor::Update(dt);
		return;
	}

	auto& input = nu::Engine::Get().GetInput();

	// top-down WASD / arrow movement
	float dx = 0.0f, dy = 0.0f;
	if (input.GetKeyDown(SDL_SCANCODE_A) || input.GetKeyDown(SDL_SCANCODE_LEFT))  dx -= 1.0f;
	if (input.GetKeyDown(SDL_SCANCODE_D) || input.GetKeyDown(SDL_SCANCODE_RIGHT)) dx += 1.0f;
	if (input.GetKeyDown(SDL_SCANCODE_W) || input.GetKeyDown(SDL_SCANCODE_UP))    dy -= 1.0f;
	if (input.GetKeyDown(SDL_SCANCODE_S) || input.GetKeyDown(SDL_SCANCODE_DOWN))  dy += 1.0f;

	nu::Vector2 velocity{ dx * m_speed, dy * m_speed };
	m_physicsComponent->SetVelocity(velocity);

	if (dx != 0.0f) m_rendererComponent->setFilpH(dx < 0.0f);   // face movement direction

	// start a sword swing on SPACE
	if (input.GetKeyPressed(SDL_SCANCODE_SPACE)) m_attackTimer = 0.5f;

	if (m_attackTimer > 0.0f)
	{
		m_attackTimer -= dt;
		m_rendererComponent->Play("attack");
	}
	else if (dx != 0.0f || dy != 0.0f)
	{
		m_rendererComponent->Play("run");
	}
	else
	{
		m_rendererComponent->Play("idle");
	}

	Actor::Update(dt);
}

void PlayerController::OnCollision(nu::Actor* actor)
{
}

void PlayerController::Read(const nu::json::value_t& value)
{
	Actor::Read(value);
	JSON_READ_NAME(value, "speed", m_speed);
}
