#include "pch.h"
#include "bullet.h"
#include "Renderer.h"

namespace nu {

    void bullet::Update(float dt) {
        m_lifespan -= dt;
        if (m_lifespan <= 0.0f) {
            Destroy();
            return;
        }
        m_tranform.position += (m_velocity * dt);
    }

    void bullet::Draw(const Renderer& renderer) const
    {
        if (m_model) renderer.DrawModel(*m_model, m_tranform);
    }

}
