#include "Player.h"
#include "Renderer.h"
#include "Engine.h"


void Player::Update(float dt) 
{
	float speed = 50.0f;
	nu::Vector2 force{ 0.0f,0.0f };
	if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
	if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;
	if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
	if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = -speed;

	setVelocity(getVelocity() + (force * dt));

	Actor::Update(dt);
}


void Player::Draw(const nu::Renderer& renderer) const 
{
	Actor::Draw(renderer);
}