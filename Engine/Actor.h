#pragma once
#include "Vector2.h"
#include "Tranform.h"

namespace nu {

    class Actor {
    public:
        Actor() = default;
        Actor(const Tranform& tranform) : m_tranform{ tranform } {

        }
        const Tranform& getTranform() const { return m_tranform; }

        void Update(float dt);
        void Draw(const class Renderer& renderer) const;
        
        void setPosistion(const Vector2& pos) { m_tranform.position = pos; }
        void setRotation(const float rotaion) { m_tranform.rotation = rotaion; }
        void setScale(const float scale) { m_tranform.scale = scale; };
        void setVelocity(const Vector2& vel) { m_velocity = vel; }
        const Vector2& getVelocity() const { return m_velocity; }
        Tranform m_tranform;
        Vector2 m_velocity {0,0};
    };
}