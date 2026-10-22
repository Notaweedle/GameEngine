#include "pch.h"
#include "RigidBodyComponent.h"
#include "Core/Factory.h"
#include "framework/Actor.h"          
#include "math/mathUitl.h"
#include <cmath>

namespace nu
{
    FACTORY_REGISTER(RigidBodyComponent)

        void RigidBodyComponent::Update(float dt)
        {
            Actor* owner = GetOwner();
            if (owner == nullptr) return;

            
            Vector2 pos = owner->getTransform().position + (m_velocity * dt);
            owner->setPosistion(pos);

            m_velocity *= std::pow(m_damping, dt);   
        }

    void RigidBodyComponent::Read(const json::value_t& value)
    {
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "damping", m_damping);
    }
}