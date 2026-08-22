#pragma once
#include "Object.h"
#include "Vector2.h"
#include "Transform.h"
#include "Model.h"
#include "json.h"
#include "Resource.h"   
#include <string>
#include <memory>
#include <Framework/Component.h>
#include "Components/ColliderComponet.h"

namespace nu {

    class Scene;
    class Texture;  

    struct ActorDesc {
        std::string name = "actor";
        std::string tag = "_actor";
        Transform transform;
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
            m_transform{ actorDesc.transform },
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


      
        explicit Actor(const Transform& transform) : m_transform{ transform } {

        }

        Actor(const Transform& transform, const Model& model) : m_transform{ transform }, m_model{ std::make_shared<Model>(model) } {

        }
        virtual ~Actor() = default;



        virtual void Update(float dt);
        virtual void Draw(const class Renderer& renderer) const;
        void Read(const nu::json::value_t& value) override;

        void DrawHitbox(const class Renderer& renderer) const;

        void AddComponet(std::unique_ptr<Component> componet);
        size_t ComponentCount() const { return m_componet.size(); }

        template <typename T>
        T* GetComponent() const
        {
            for (auto& comp : m_componet)
            {
                T* result = dynamic_cast<T*>(comp.get());
                if (result) return result;
            }
            return nullptr;
        }
        void Destroy() { m_destroyed = true; }

        bool IsDestroyed() const { return m_destroyed; }
        void SetRadius(float radius) { m_radius = radius; }
        void SetModel(std::shared_ptr<Model> model) { m_model = model; }
        void SetTexture(res_t<Texture> texture) { m_texture = texture; }
        void setTransform(const Transform& transform) { m_transform = transform; }

        
        void setPosistion(const Vector2& pos) { m_transform.position = pos; }
        void setRotation(const float rotaion) { m_transform.rotation = rotaion; }
        void setScale(const float scale) { m_transform.scale = scale; };
        void setVelocity(const Vector2& vel) { m_velocity = vel; }
        void setName(const std::string& name) { Object::m_name = name; }
        void setTag(const std::string& tag) { m_tag = tag; }

        inline float getRadius() const
        {
            if (const ColilliderComponent* collider = GetComponent<ColilliderComponent>())
            {
                if (collider->GetRadius() > 0.0f) return collider->GetRadius();
            }
            if (m_radius > 0.0f) return m_radius;
            return m_model ? m_model->GetRadius() * m_transform.scale : 0.0f;
        }
        inline const Vector2& getVelocity() const { return m_velocity; }
        inline const std::string& getTag() const { return m_tag; }
        inline float getLifeSpan() const { return m_lifespan; }
        inline float getDamping() const { return m_damping; }
        inline const Transform& getTransform() const { return m_transform; }
        inline const Scene* getScene() const { return m_scene; }
        inline res_t<Texture> getTexture() const { return m_texture; }



        inline bool isActor() const { return true; }

        void addComponent(std::unique_ptr<Component> comp);

        bool CheckCollision(const Actor& other) const
        {
            float distance = (m_transform.position - other.m_transform.position).Length();
            return distance <= (getRadius() + other.getRadius());
        }

       


        

        friend Scene;

    protected:
        Transform m_transform;
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
    

    public:

        bool operator==(const Actor& other) const = default;
    };
}