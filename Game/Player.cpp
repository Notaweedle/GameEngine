#include "Player.h"
#include "Renderer.h"
#include "Engine.h"


void Player::Update(float dt) 
{
	float speed = 2000.0f;
	nu::Vector2 force{ 0.0f,0.0f };
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;

	setVelocity(getVelocity() + (force * dt));

	// Rotation input: Q / E turn the ship (radians per second).
	float turnSpeed = 6.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_Q)) setRotation(getTranform().rotation - turnSpeed * dt);
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_E)) setRotation(getTranform().rotation + turnSpeed * dt);

	Actor::Update(dt);
}


void Player::Draw(const nu::Renderer& renderer) const 
{
	Actor::Draw(renderer);
}