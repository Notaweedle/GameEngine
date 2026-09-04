#pragma once
#include "Framework/Actor.h"

namespace nu {
	class PhysicsComponent;
	class SpriteAnimatorRendererComponet;
}

class PlayerController : public nu::Actor
{
public:
	CLASS_PROTOTYPE(PlayerController)

	void Start() override;
	void Update(float dt) override;

	void OnCollision(nu::Actor* actor) override;
	void Read(const nu::json::value_t& value) override;

	void Die() { m_dead = true; }        // play death anim + stop the player
	bool IsDead() const { return m_dead; }

protected:
	float m_speed = 300.0f;   // pixels / second
	float m_attackTimer = 0.0f;   // >0 while the swing animation plays
	bool  m_dead = false;

	nu::PhysicsComponent* m_physicsComponent = nullptr;
	nu::SpriteAnimatorRendererComponet* m_rendererComponent = nullptr;
};
