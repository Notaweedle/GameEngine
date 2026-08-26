#include "pch.h"
#include "Enemy.h"
#include "Renderer.h"
#include "math/mathUitl.h"
#include "Random.h"
#include "Scene.h"
#include "../Game/Assets.h"
#include "ResourceManager.h"
#include "Texture.h"
//#include "Engine.h"
#include "Factory.h"
#include <cmath>
#include <Json.h>


namespace nu {
    FACTORY_REGISTER(Enemy);
    
    void Enemy::Update(float dt) {
        Actor const* player = (m_scene) ? m_scene->GetActorByName<Actor>("Player") : nullptr;
        if (player) {
            nu::Vector2 direction = player->getTransform().position - m_transform.position;

            float rotation = direction.Angle();
            setRotation(rotation);

            
            nu::Vector2 forword = nu::Vector2{ 1, 0 }.Rotate(m_transform.rotation);
            m_velocity += forword * m_speed * dt;
        }

        m_transform.position += (m_velocity * dt);
        m_velocity *= std::pow(0.02f, dt);   
        

    }
    

    void Enemy::Draw(const Renderer& renderer) const
    {
        if (m_texture)
            renderer.DrawTexture(m_texture.get(), m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
        else if (m_model)
            renderer.DrawModel(*m_model, m_transform);
    }

    void Enemy::OnKilled()
    {
        Destroy();

        if (m_scene == nullptr) return;

        
        if (m_name.find("yeedi") == std::string::npos) return;
        if (RandomFloat() > 0.5f) return;

        float angle = RandomFloat(0.0f, 6.28f);

        for (int i = 0; i < 2; i++) {

            float dir = angle + (i * math::pi);
            Vector2 vel = Vector2{ std::cos(dir), std::sin(dir) } * 200.0f;

            auto trita = Factory::Instance().Create<Actor>("trita");
            if (trita == nullptr) { continue; }
            trita->setPosistion(m_transform.position);
            trita->setRotation(dir);
            trita->setVelocity(vel);

            m_scene->AddActor(std::move(trita));
        }
    }

     

    void Enemy::Read(const nu::json::value_t& value)  {
        Actor::Read(value);

       
        JSON_READ_NAME(value, "health", m_health);
        JSON_READ_NAME(value, "speed", m_speed);
        JSON_READ_NAME(value, "speed", m_speed);    
    }
}