#pragma once
#include "Vector2.h"
#include "Tranform.h"
#include "Model.h"
#include <string>
#include <memory>

namespace nu {

    
    class Scene;

    struct ActorDesc {
        std::string name;
        std::string tag;

        Tranform transform;
        Vector2 velocity;
        std::shared_ptr<Model> model;
    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_tranform{ actorDesc.transform },
            m_name{actorDesc.name},
            m_tag{actorDesc.tag},
            m_velocity{ actorDesc.velocity },
            m_model{ actorDesc.model } 
        {};

        Actor(const Tranform& tranform) : m_tranform{ tranform } {

        }

        Actor(const Tranform& tranform, const Model& model) : m_tranform{ tranform }, m_model{ std::make_shared<Model>(model) } {

        }
        virtual ~Actor() = default;

        const Tranform& getTranform() const { return m_tranform; }

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;

        
        void DrawHitbox(const class Renderer& renderer) const;

        void Destroy() { m_destroyed = true; }
        bool IsDestroyed() const { return m_destroyed; }

        float GetRadius() const { return m_model ? m_model->GetRadius() * m_tranform.scale : 0.0f; }
        void SetModel(std::shared_ptr<Model> model) { m_model = model; }

        bool CheckCollision(const Actor& other) const
        {
            float distance = (m_tranform.position - other.m_tranform.position).Length();
            return distance <= (GetRadius() + other.GetRadius());
        }

        void setPosistion(const Vector2& pos) { m_tranform.position = pos; }
        void setRotation(const float rotaion) { m_tranform.rotation = rotaion; }
        void setScale(const float scale) { m_tranform.scale = scale; };
        void setVelocity(const Vector2& vel) { m_velocity = vel; }
        void setName(const std::string& name) { m_name = name; }
        void setTag(const std::string& tag) { m_tag = tag; }

        const Vector2& getVelocity() const { return m_velocity; }
        const std::string& getName() const { return m_name; }
        const std::string& getTag() const { return m_tag; }

        Scene* getScene() { return m_scene; }


        friend Scene;

    protected:
        Tranform m_tranform;
        std::string m_name;
        std::string m_tag;
        Vector2 m_velocity {0,0};
        std::shared_ptr<Model> m_model;

        bool m_destroyed = false;
        Scene* m_scene{ nullptr };
    };
}