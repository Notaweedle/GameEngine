#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "mathUitl.h"
#include <cmath>



namespace nu {
   
    void Actor::Update(float dt) {
        m_tranform.position += (m_velocity * dt);
        m_velocity *= std::pow(0.05f, dt);

        m_tranform.position.x = math::Wrap(0.0f, 2560.0f, m_tranform.position.x);
        m_tranform.position.y = math::Wrap(0.0f, 1600.0f, m_tranform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        // Prefer a texture (sprite) if this actor has one; otherwise draw the vector model.
        if (m_texture)
            renderer.DrawTexture(m_texture.get(), m_tranform.position.x, m_tranform.position.y, m_tranform.rotation, m_tranform.scale);
        else if (m_model)
            renderer.DrawModel(*m_model, m_tranform);
    }

    void Actor::DrawHitbox(const Renderer& renderer) const
    {
        renderer.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
        renderer.DrawCircle(m_tranform.position.x, m_tranform.position.y, GetRadius());
    }

}