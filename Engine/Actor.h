#pragma once
#include "Vector2.h"
#include "Tranform.h"
#include "Model.h"
#include <string>

namespace nu {

    struct ActorDesc {
        std::string name;
        std::string tag;

        Tranform transform;
        Vector2 velocity;
        Model model;
    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_tranform{ actorDesc.transform },
            m_velocity{ actorDesc.velocity },
            m_model{ actorDesc.model } 
        {};

        Actor(const Tranform& tranform) : m_tranform{ tranform } {

        }

        Actor(const Tranform& tranform, const Model& model) : m_tranform{ tranform }, m_model{ model } {

        }
        const Tranform& getTranform() const { return m_tranform; }

        void Update(float dt);
        void Draw(const class Renderer& renderer) const;

        void setPosistion(const Vector2& pos) { m_tranform.position = pos; }
        void setRotation(const float rotaion) { m_tranform.rotation = rotaion; }
        void setScale(const float scale) { m_tranform.scale = scale; };
        void setVelocity(const Vector2& vel) { m_velocity = vel; }
        const Vector2& getVelocity() const { return m_velocity; }
        const std::string& getName() const { return m_name; }
        const std::string& getTag() const { return m_tag; }

    protected:
        Tranform m_tranform;
        std::string m_name;
        std::string m_tag;
        Vector2 m_velocity {0,0};
        Model m_model;
    };
}