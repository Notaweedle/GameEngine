#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "mathUitl.h"



namespace nu {
   

    void Actor::Update(float dt) {
        m_tranform.position += (m_velocity * dt);
        m_velocity *= 0.987f;

        m_tranform.position.x = math::Wrap(0.0f, 1280.0f, m_tranform.position.x);
        m_tranform.position.y = math::Wrap(0.0f, 1024.0f, m_tranform.position.y);
    }

    void Actor::Draw(const Renderer& renderer) const
    {
        renderer.DrawModel(m_model, m_tranform);
    }

}