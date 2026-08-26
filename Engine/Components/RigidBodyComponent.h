#pragma once
#include "Framework/Component.h"
#include "math/Vector2.h"
#include "json.h"

namespace nu
{
    class RigidBodyComponent : public Component
    {
    public:
        CLASS_PROTOTYPE(RigidBodyComponent)

            void Update(float dt) override;
        void Read(const json::value_t& value) override;

    protected:
        Vector2 m_velocity{ 0.0f, 0.0f };
        float   m_damping = 0.0f;
    };
}