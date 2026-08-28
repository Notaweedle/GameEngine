#include "Player.h"
#include "renderer/Renderer.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "core/bullet.h"
#include "Renderer/ParticleSystem.h"
#include "Assets.h"
#include "math/mathUitl.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture.h"
#include "Core/Factory.h"

#include <iostream>
#include <memory>

FACTORY_REGISTER(Player);


void Player::Update(float dt) 
{
	float speed = 4000.0f;
	nu::Vector2 forword = { std::cos(getTransform().rotation),
							std::sin(getTransform().rotation)};
	nu::Vector2 force{ 0.0f,0.0f };

	
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)|| nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_UP)) {
		force = forword * speed;

		//TODO Remake this to use factorys 
		nu::ParticleDesc pd;
		pd.position = getTransform().position - forword * 20.0f;
		pd.angle = getTransform().rotation + nu::math::pi;
		pd.angleVariance = 0.3f;
		pd.speed = 120.0f;
		pd.speedVariance = 40.0f;
		pd.lifetime = 0.4f;
		pd.lifetimeVariance = 0.15f;
		pd.color = nu::Color{ 0.3f, 0.6f, 1.0f, 1.0f }; 
		pd.count = 10;
		nu::Engine::Get().GetParticleSystem().Emit(pd);
	}
	

	

	
	float turnSpeed = 8.0f;
	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)||
		nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_LEFT)) setRotation(getTransform().rotation - turnSpeed * dt);

	if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)||
		nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_RIGHT)) setRotation(getTransform().rotation + turnSpeed * dt);

	setVelocity(getVelocity() + (force * dt));

	Shoot();

	Actor::Update(dt);
}

void Player::Shoot() {
	if (!nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_Q)|| nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE)) return;
	if (getScene() == nullptr) return;

	nu::Vector2 forword = { std::cos(getTransform().rotation),
							std::sin(getTransform().rotation) };

	
	auto bullet = nu::Factory::Instance().Create<nu::Bullet>("bulletPrototype");
	if (bullet == nullptr) return;
	//TODO Upadte to use factorys 
	nu::Transform t = getTransform();
	t.position = getTransform().position + (forword * 30.0f); 
	bullet->setTransform(t);
	bullet->setVelocity(forword * m_bulletSpeed);
	bullet->SetRadius(15.0f);

	m_scene->AddActor(std::move(bullet));

	nu::Engine::Get().GetAudio().PlaySound("laser");
}

void Player::Draw(const nu::Renderer& renderer) const
{
	Actor::Draw(renderer);
}

void Player::Read(const nu::json::value_t& value) {
	Actor::Read(value);

	JSON_READ_NAME(value, "speed", m_speed);

	JSON_READ_NAME(value, "tag", m_tag);
	JSON_READ_NAME(value, "name", m_name);

	if (JSON_HAS_NAME(value, "bulletSpeed"))
		JSON_READ_NAME(value, "bulletSpeed", m_bulletSpeed);
}