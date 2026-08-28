#include "pch.h"
#include "bullet.h"
#include "Renderer/Renderer.h"
#include "Factory.h"
#include <Serialization/Json.h>

namespace nu {

    
    FACTORY_REGISTER(Bullet);

    void Bullet::Update(float dt) {
        m_lifespan -= dt;
        if (m_lifespan <= 0.0f) {
            Destroy();
            return;
        }
        m_transform.position += (m_velocity * dt);
    }

    void Bullet::Draw(const Renderer& renderer) const
    {
        if (m_texture)
            renderer.DrawTexture(m_texture.get(), m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
        else if (m_model)
            renderer.DrawModel(*m_model, m_transform);
    }


    void Bullet::Read(const nu::json::value_t& value) {
        Actor::Read(value);

        JSON_READ_NAME(value, "speed", m_speed);
    }

}
