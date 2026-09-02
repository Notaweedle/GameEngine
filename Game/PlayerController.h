#pragma once
#include "Framework\Actor.h"



namespace nu {

	class PhysicsComponent;
	class SpriteAnimationRendererComponent;
}

class PlayerController : public nu::Actor
{
public:
	CLASS_PROTOTYPE(PlayerController)

	void Start() override;
	void Update(float dt) override;

	void OnCollision(nu::Actor* actor) override;
	void Read(const nu::json::value_t& value) override;

protected:
	 nu::PhysicsComponent* m_physicsComponent = nullptr;
	 nu::SpriteAnimationRendererComponent* m_rendererComponent = nullptr;

};

