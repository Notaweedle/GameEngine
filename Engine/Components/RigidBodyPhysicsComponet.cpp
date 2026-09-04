#include "pch.h"
#include "RigidBodyPhysicsComponet.h"
#include "Core/Factory.h"
#include "Core/StringUtil.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include "Physics/Physics.h"
#include "Math/mathUitl.h"

namespace nu {

    FACTORY_REGISTER(RigidBodyPhysicsComponent)

    void RigidBodyPhysicsComponent::Start()
    {
        m_bodyDef.actor = GetOwner();

        // build the box2d body in the engine's physics world using this actor's transform
        m_physicsBody = std::make_unique<PhysicsBody>(
            GetOwner()->getTransform(),
            m_size,
            m_bodyDef,
            Engine::Get().GetPhysics());
    }

    void RigidBodyPhysicsComponent::Update(float dt)
    {
        if (!m_physicsBody) return;

       
        Vector2 pos = m_physicsBody->GetPosition();

        
        if (m_bodyDef.wrap)
        {
            Vector2 wrapped{ math::Wrap(0.0f, 2560.0f, pos.x), math::Wrap(0.0f, 1600.0f, pos.y) };
            if (wrapped.x != pos.x || wrapped.y != pos.y) m_physicsBody->SetPosition(wrapped);
            pos = wrapped;
        }

        GetOwner()->setPosistion(pos);
        GetOwner()->setRotation(m_physicsBody->GetRotation());
    }

    void RigidBodyPhysicsComponent::ApplyForce(const Vector2& force)
    {
        if (m_physicsBody) m_physicsBody->ApplyForce(force);
    }

    void RigidBodyPhysicsComponent::SetVelocity(const Vector2& velocity)
    {
        if (m_physicsBody) m_physicsBody->SetVelocity(velocity);
    }

    Vector2 RigidBodyPhysicsComponent::GetVelocity()
    {
        return m_physicsBody ? m_physicsBody->GetVelocity() : Vector2{ 0.0f, 0.0f };
    }

    void RigidBodyPhysicsComponent::ApplyTorque(float torque)
    {
        if (m_physicsBody) m_physicsBody->ApplyTorque(torque);
    }

    void RigidBodyPhysicsComponent::SetAngularVelocity(float angularVelocity)
    {
        if (m_physicsBody) m_physicsBody->SetAngularVelocity(angularVelocity);
    }

    float RigidBodyPhysicsComponent::GetAngularVelocity() const
    {
        return m_physicsBody ? m_physicsBody->GetAngularVelocity() : 0.0f;
    }

    void RigidBodyPhysicsComponent::SetPosition(const Vector2& position)
    {
        if (m_physicsBody) m_physicsBody->SetPosition(position);
    }

    Vector2 RigidBodyPhysicsComponent::GetPosition() const
    {
        return m_physicsBody ? m_physicsBody->GetPosition() : GetOwner()->getTransform().position;
    }

    void RigidBodyPhysicsComponent::Read(const json::value_t& value)
    {
        PhysicsComponent::Read(value);

        JSON_READ_NAME(value, "size", m_size);
        JSON_READ_NAME(value, "scale", m_scale);
        JSON_READ_NAME(value, "gravity_scale", m_bodyDef.gravityScale);
        JSON_READ_NAME(value, "linear_damping", m_bodyDef.linearDamping);
        JSON_READ_NAME(value, "angular_damping", m_bodyDef.angularDamping);
        JSON_READ_NAME(value, "constrain_angle", m_bodyDef.constrainAngle);
        JSON_READ_NAME(value, "is_dynamic", m_bodyDef.isDynamic);
        JSON_READ_NAME(value, "wrap", m_bodyDef.wrap);
        JSON_READ_NAME(value, "friction", m_bodyDef.friction);
        JSON_READ_NAME(value, "restitution", m_bodyDef.restitution);
        JSON_READ_NAME(value, "density", m_bodyDef.density);
        JSON_READ_NAME(value, "is_sensor", m_bodyDef.isSensor);

        std::string shapeName;
        JSON_READ_NAME(value, "shape", shapeName);
        if (!shapeName.empty())
        {
            if (EqualsIgnoreCase(shapeName, "box"))          m_bodyDef.shape = PhysicsBody::Shape::Box;
            else if (EqualsIgnoreCase(shapeName, "capsule")) m_bodyDef.shape = PhysicsBody::Shape::Capsule;
            else if (EqualsIgnoreCase(shapeName, "circle"))  m_bodyDef.shape = PhysicsBody::Shape::Circle;
        }
    }
}
