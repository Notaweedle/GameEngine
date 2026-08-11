#pragma once
#include "Vector2.h"
#include "Tranform.h"
#include "Model.h"
#include "Resource.h"   // res_t template alias
#include <string>
#include <memory>

namespace nu {

    class Scene;
    class Texture;   // res_t<Texture> below only needs a forward declaration

    struct ActorDesc {
        std::string name;
        std::string tag;

        Tranform transform;
        Vector2 velocity{ 0.0f, 0.0f };   // must be zero-initialized; Vector2's default leaves it garbage
        float damping{ 0.f };
        float lifespan{ 0.f };
        res_t<Model> model;
        res_t<Texture> texture;
    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_tranform{ actorDesc.transform },
            m_name{actorDesc.name},
            m_tag{actorDesc.tag},
            m_velocity{ actorDesc.velocity },
            m_model{ actorDesc.model },
            m_texture{ actorDesc.texture }
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

        // Collision radius: an explicit radius (set via SetRadius) wins; otherwise
        // fall back to the vector model's radius * scale. Sprites have no model, so
        // they need SetRadius to get a hitbox.
        float GetRadius() const
        {
            if (m_radius > 0.0f) return m_radius;
            return m_model ? m_model->GetRadius() * m_tranform.scale : 0.0f;
        }
        void SetRadius(float radius) { m_radius = radius; }
        void SetModel(std::shared_ptr<Model> model) { m_model = model; }
        void SetTexture(res_t<Texture> texture) { m_texture = texture; }

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
        res_t<Model> m_model;
        res_t<Texture> m_texture;
        float m_radius = 0.0f;   // explicit collision radius (0 = use model)

        bool m_destroyed = false;
        Scene* m_scene{ nullptr };
    };
}