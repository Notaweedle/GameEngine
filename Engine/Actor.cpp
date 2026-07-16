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
        /*renderer.SetColor(1.0f, 1.0f, 1.0f);
        renderer.DrawFillRect(m_tranform.position.x - (m_tranform.scale * 0.5f),m_tranform.position.y - ((m_tranform.scale * 0.5f)),m_tranform.scale, m_tranform.scale);*/
    }

}