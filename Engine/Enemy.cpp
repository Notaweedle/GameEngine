#include "pch.h"
#include "Enemy.h"
#include "Renderer.h"
#include "mathUitl.h"
#include "Scene.h"   


namespace nu {


    void Enemy::Update(float dt) {
        Actor* player = m_scene->GetActorByName<Actor>("Player");
        if (player) {
            nu::Vector2 direction = player->getTranform().position - m_tranform.position;
            
            float rotation = direction.Angle();
            setRotation(rotation);

            
            nu::Vector2 forword = nu::Vector2{ 1, 0 }.Rotate(m_tranform.rotation);
            
        }

        float trust = 0.0f;
        float rotate = 0.0f;

        
        

        m_tranform.position += (m_velocity * dt);
        m_velocity *= 0.987f;

        m_tranform.position.x = math::Wrap(0.0f, 1280.0f, m_tranform.position.x);
        m_tranform.position.y = math::Wrap(0.0f, 1024.0f, m_tranform.position.y);
    }

    void Enemy::Draw(const Renderer& renderer) const
    {
        renderer.DrawModel(m_model, m_tranform);
    }

}