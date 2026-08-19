#pragma once
#include "Object.h"
#include "Vector2.h"
#include "Tranform.h"
#include "Model.h"
#include "Resource.h"   
#include <string>
#include <memory>
#include <Framework/Component.h>

namespace nu {

    class Scene;
    class Texture;  

    struct ActorDesc {
        std::string name = "actor";
        std::string tag = "_actor";
        Tranform transform;
        Vector2 velocity{ 0.0f, 0.0f };   
        float damping{ 0.f };
        float lifespan{ 0.f };
        res_t<Model> model;
        res_t<Texture> texture;
    };

    class Actor : public Object {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            Object(),
            m_tranform{ actorDesc.transform },
            m_tag{ actorDesc.tag },
            m_velocity{ actorDesc.velocity },
            m_model{ actorDesc.model },
            m_texture{ actorDesc.texture },
            m_lifespan{actorDesc.lifespan},
            m_damping{actorDesc.damping }
        {

            Object::m_name = { actorDesc.name };
        };
        Actor(const Actor& other);

        CLASS_PROTOTYPE(Actor)

        Actor(const Tranform& tranform) : m_tranform{ tranform } {

        }

        Actor(const Tranform& tranform, const Model& model) : m_tranform{ tranform }, m_model{ std::make_shared<Model>(model) } {

        }
        virtual ~Actor() = default;


        const void setTranform(const Tranform& trandform) { m_tranform = trandform; }
        const Tranform& getTranform() const { return m_tranform; }

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;


        void DrawHitbox(const class Renderer& renderer) const;

        void AddComponet(std::unique_ptr<Component> componet);

        void Destroy() { m_destroyed = true; }
        bool IsDestroyed() const { return m_destroyed; }
        float GetRadius() const
        {
            if (m_radius > 0.0f) return m_radius;
            return m_model ? m_model->GetRadius() * m_tranform.scale : 0.0f;
        }
        void SetRadius(float radius) { m_radius = radius; }
        void SetModel(std::shared_ptr<Model> model) { m_model = model; }
        void SetTexture(res_t<Texture> texture) { m_texture = texture; }

        
        void setPosistion(const Vector2& pos) { m_tranform.position = pos; }
        void setRotation(const float rotaion) { m_tranform.rotation = rotaion; }
        void setScale(const float scale) { m_tranform.scale = scale; };
        void setVelocity(const Vector2& vel) { m_velocity = vel; }
        void setName(const std::string& name) { Object::m_name = name; }
        void setTag(const std::string& tag) { m_tag = tag; }

        inline const Vector2& getVelocity() const { return m_velocity; }
        inline const std::string& getTag() const { return m_tag; }
        inline float getLifeSpan() const { return m_lifespan; }
        inline float getDamping() const { return m_damping; }
        inline bool isActor() const { return true; }

        void addComponent(std::unique_ptr<Component> comp);

        bool CheckCollision(const Actor& other) const
        {
            float distance = (m_tranform.position - other.m_tranform.position).Length();
            return distance <= (GetRadius() + other.GetRadius());
        }


        Scene* getScene() { return m_scene; }
        

        friend Scene;

    protected:
        Tranform m_tranform;
        std::string m_tag = "_actor";
        Vector2 m_velocity {0,0};
        res_t<Model> m_model = nullptr;
        res_t<Texture> m_texture = nullptr;
        float m_radius = 0.0f;   
        float m_lifespan = 0.0f;
        float m_damping = 0.0f;
        bool m_destroyed = false;
        Scene* m_scene{ nullptr };

        std::vector<std::unique_ptr<Component>> m_componet;
    

    };


   /* template <std::derived_from<Component> T>
    inline T* Actor::GetComponent()
    {
        for (auto& comp : m_componet) 
        {
            auto
        }
    }*/

}