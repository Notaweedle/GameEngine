#include "pch.h"
#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Math/mathUitl.h"
#include <cmath>
#include "Engine.h"
#include "Components/RendererComponent.h"
#include "Resources/ResourceManager.h"
#include "Renderer/Texture.h"
#include <Serialization/Json.h>






namespace nu {
   
    FACTORY_REGISTER(Actor);

    Actor::Actor(const Actor& other) :
        Object{ other },
        m_transform{ other.m_transform },
        m_tag{ other.m_tag },
        m_velocity{ other.m_velocity },
        m_model{ other.m_model },
        m_texture{ other.m_texture },
        m_radius{ other.m_radius },
        m_lifespan{ other.m_lifespan },
        m_damping{ other.m_damping }{

        for (const auto& comp : other.m_componet)
        {
            std::unique_ptr<Object> objClone = comp->Clone();
            Component* compClone = dynamic_cast<Component*>(objClone.release());
            if (compClone)
            {
                AddComponet(std::unique_ptr<Component>(compClone));
            }
        }

    }

    void Actor::Update(float dt) {
            
        for (auto const& component : m_componet) component->Update(dt);

        m_transform.position += (m_velocity * dt);
        m_velocity *= std::pow(0.05f, dt);

        m_transform.position.x = math::Wrap(0.0f, 2560.0f, m_transform.position.x);
        m_transform.position.y = math::Wrap(0.0f, 1600.0f, m_transform.position.y);


    
        

    }

    void Actor::Draw(const Renderer& renderer) const
    {
        for (auto& component : m_componet) 
        {
            auto renderercomponent = dynamic_cast<RendererComponent*>(component.get());

            if (renderercomponent) {
                renderercomponent->Draw(renderer);
            }
        }
    }

    void Actor::DrawHitbox(const Renderer& renderer) const
    {
        renderer.SetColor(0.0f, 1.0f, 0.0f, 1.0f);
        renderer.DrawCircle(m_transform.position.x, m_transform.position.y, getRadius());
    }

    void Actor::AddComponet(std::unique_ptr<Component> componet) {

        componet->SetOwner(this);
        m_componet.push_back(std::move(componet));
    }   

    void Actor::Read(const json::value_t& value)
    {
        Object::Read(value);

        JSON_READ_NAME(value, "tag", m_tag);
        JSON_READ_NAME(value, "transform", m_transform);
        JSON_READ_NAME(value, "velocity", m_velocity);
        JSON_READ_NAME(value, "damping", m_damping);

       
        if (JSON_HAS_NAME(value, "texture"))
        {
            std::string texture;
            if (JSON_READ_NAME(value, "texture", texture) && !texture.empty())
                m_texture = Resources().Get<Texture>(texture, Engine::Get().GetRenderer());
        }


        
        if (JSON_HAS_NAME(value, "components") && JSON_GET_NAME(value, "components").IsArray())
        {
            for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray())
            {
                std::string type;
                JSON_READ_NAME(componentValue, "type", type);

                auto component = Factory::Instance().Create<Component>(type);
                if (component)                      
                {
                    component->Read(componentValue);
                    AddComponet(std::move(component));
                }
            }
        }
    }

     void Actor::Start() {
         for (auto& component : m_componet)
         {
             component->Start();
         }
     };

     void Actor::OnDestroy() {
         for (auto& component : m_componet)
         {
             component->onDestroy();
         }
     };

}