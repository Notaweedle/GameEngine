#include "pch.h"
#include "bullet.h"
#include "Renderer.h"

namespace nu {

    void Bullet::Update(float dt) {
        m_lifespan -= dt;
        if (m_lifespan <= 0.0f) {
            Destroy();
            return;
        }
        m_tranform.position += (m_velocity * dt);
    }

    void Bullet::Draw(const Renderer& renderer) const
    {
        if (m_texture)
            renderer.DrawTexture(m_texture.get(), m_tranform.position.x, m_tranform.position.y, m_tranform.rotation, m_tranform.scale);
        else if (m_model)
            renderer.DrawModel(*m_model, m_tranform);
    }

}
