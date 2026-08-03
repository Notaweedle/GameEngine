#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "Scene.h"
#include "bullet.h"
#include "ParticleSystem.h"
#include <iostream>
#include <memory>
#include "Assets.h"
#include "mathUitl.h"



void Player::Update(float dt) 
{
	float speed = 6000.0f;
	nu::Vector2 forword = { std::cos(getTranform().rotation),
							std::sin(getTranform().rotation)};
	nu::Vector2 force{ 0.0f,0.0f };

	
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)|| nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)) {
		force = forword * speed;

		
		nu::ParticleDesc pd;
		pd.position = getTranform().position - forword * 20.0f;
		pd.angle = static_cast<float>(getTranform().rotation + nu::math::pi);
		pd.angleVariance = 0.3f;
		pd.speed = 120.0f;
		pd.speedVariance = 40.0f;
		pd.lifetime = 0.4f;
		pd.lifetimeVariance = 0.15f;
		pd.color = nu::Color{ 0.3f, 0.6f, 1.0f, 1.0f }; 
		pd.count = 3;
		nu::Engine::Get().GetParticleSystem().Emit(pd);
	}
	

	

	
	float turnSpeed = 8.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)||
		nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) setRotation(getTranform().rotation - turnSpeed * dt);

	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)||
		nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) setRotation(getTranform().rotation + turnSpeed * dt);

	setVelocity(getVelocity() + (force * dt));

	Shoot();

	Actor::Update(dt);
}

void Player::Shoot() {
	if (!nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_Q)|| nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) return;
	if (getScene() == nullptr) return;

	nu::Vector2 forword = { std::cos(getTranform().rotation),
							std::sin(getTranform().rotation) };

	nu::Tranform tranform{ getTranform().position + (forword * 30.0f),
						   getTranform().rotation,
						   5.0f };

	auto bullet = std::make_unique<nu::bullet>(m_bulletSpeed, tranform, Assets::model_bullet);
	bullet->setName("bullet");
	bullet->setTag("bullet");
	bullet->setVelocity(forword * m_bulletSpeed);

	getScene()->AddActor(std::move(bullet));

	nu::Engine::Get().GetAudio().PlaySound("laser");
}

void Player::Draw(const nu::Renderer& renderer) const
{
	// Was declared 'override' in Player.h but never defined -> unresolved external.
	Actor::Draw(renderer);
}