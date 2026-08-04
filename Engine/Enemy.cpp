#include "pch.h"
#include "Enemy.h"
#include "Renderer.h"
#include "mathUitl.h"
#include "Random.h"
#include "Scene.h"
#include "../Game/Assets.h"
#include <cmath>


namespace nu {

    
    void Enemy::Update(float dt) {
        Actor* player = (m_scene) ? m_scene->GetActorByName<Actor>("Player") : nullptr;
        if (player) {
            nu::Vector2 direction = player->getTranform().position - m_tranform.position;

            float rotation = direction.Angle();
            setRotation(rotation);

            
            nu::Vector2 forword = nu::Vector2{ 1, 0 }.Rotate(m_tranform.rotation);
            m_velocity += forword * m_speed * dt;
        }

        m_tranform.position += (m_velocity * dt);
        m_velocity *= 0.987f;
        

    }
    

    void Enemy::Draw(const Renderer& renderer) const
    {
        if (m_model) renderer.DrawModel(*m_model, m_tranform);
    }

    void Enemy::OnKilled()
    {
        Destroy();

        if (m_scene == nullptr) return;
        if (m_name.find("yeedi_") == std::string::npos) return;
        if (RandomFloat() > 0.5f) return;
        float angle = RandomFloat(0.0f, 6.28f);

        for (int i = 0; i < 2; i++) {
            float dir = angle + (i * 3.14159f);
            Vector2 vel = Vector2{ std::cos(dir), std::sin(dir) } *200.0f;

            auto frag = std::make_unique<Enemy>(
                2500.0f,
                Tranform{ m_tranform.position, dir, 7.0f },
                *Assets::model_triangle
            );
            frag->setName("triangle_" + std::to_string(i));
            frag->setTag("enemy");
            frag->setVelocity(vel);
            m_scene->AddActor(std::move(frag));
        }
    }

    void Enemy::SpawnAtEdges(Scene& scene, int count, float worldW, float worldH) {
        const float MARGIN = 20.0f;

        for (int i = 0; i < count; i++) {
            float x, y;
            int edge = rand() % 4;

            switch (edge) {
            case 0: x = nu::math::randomf(0.0f, worldW); y = -MARGIN;          break;
            case 1: x = nu::math::randomf(0.0f, worldW); y = worldH + MARGIN;  break;
            case 2: x = -MARGIN;          y = nu::math::randomf(0.0f, worldH);  break;
            case 3: x = worldW + MARGIN;  y = nu::math::randomf(0.0f, worldH);  break;
            }

            auto enemy = std::make_unique<Enemy>(
                2000.0f,
                Tranform{ Vector2{x, y}, 0.0f, 12.0f },
                *Assets::model_yeedi
            );

            auto rainDrop = std::make_unique<Enemy>(
                3500.0f,
                Tranform{ Vector2{x,y}, 0.0f, 25.f },
                *Assets::model_raincol
            );

            enemy->setName("yeedi_" + std::to_string(i));
            rainDrop->setName("rainDrop_" + std::to_string(i));

            enemy->setTag("enemy");
            rainDrop->setTag("enemy");

            if (math::randomf(0.0f, 1.f) <= 0.1f) {
                scene.AddActor(std::move(rainDrop));
            }else{
                scene.AddActor(std::move(enemy));
            }

            
        }
    }
}