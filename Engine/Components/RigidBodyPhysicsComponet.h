#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsBody.h"
#include <memory>

namespace nu {

	
	class RigidBodyPhysicsComponent : public PhysicsComponent {
	public:
		CLASS_PROTOTYPE(RigidBodyPhysicsComponent);

		RigidBodyPhysicsComponent() = default;
		// copy ctor for cloning: copy the body DEFINITION, not the live body.
		// (unique_ptr<PhysicsBody> isn't copyable; Start() rebuilds the body on the clone)
		RigidBodyPhysicsComponent(const RigidBodyPhysicsComponent& other)
			: m_size{ other.m_size }, m_scale{ other.m_scale }, m_bodyDef{ other.m_bodyDef } {}

		void Start() override;
		void Update(float dt) override;

		void ApplyForce(const Vector2& force) override;
		void SetVelocity(const Vector2& velocity) override;
		Vector2 GetVelocity() override;

		void ApplyTorque(float torque) override;
		void SetAngularVelocity(float angularVelocity) override;
		float GetAngularVelocity() const override;

		void SetPosition(const Vector2& position) override;
		Vector2 GetPosition() const override;

		void Read(const json::value_t& value) override;

	private:
		Vector2 m_size{ 1.0f, 1.0f };
		float   m_scale{ 1.0f };

		PhysicsBody::PhysicsBodyDef  m_bodyDef;
		std::unique_ptr<PhysicsBody> m_physicsBody;
	};

}
