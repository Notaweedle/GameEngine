#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "mathUitl.h"
#include <cmath>
#include "Engine.h"
#include "Components/RendererComponent.h"






namespace nu {
   
    FACTORY_REGISTER(Actor);

    

    Actor::Actor(const Actor& other) :
        Object{ other },
        m_tranform{other.m_tranform },
        m_tag{ other.m_tag },
        m_damping{other.m_damping },
        m_lifespan{other.m_lifespan }
    {
        for (const  auto& comp: other.m_componet )
        {
           /* std::unique_ptr<Object> objClone = comp->Clone();
            Component* compClone = dynamic_cast<Component*>(objClone.release());
            if (compClone)
            {
                AddComponet(std::unique_ptr<Component>(compClone));
            }*/
        }

    }

    void Actor::Update(float dt) {
            
        if (Actor::getLifeSpan() > 0.0f) 
        {
        
        }

        m_tranform.position += (m_velocity * dt);
        m_velocity *= std::pow(0.05f, dt);

        m_tranform.position.x = math::Wrap(0.0f, 2560.0f, m_tranform.position.x);
        m_tranform.position.y = math::Wrap(0.0f, 1600.0f, m_tranform.position.y);
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
        renderer.DrawCircle(m_tranform.position.x, m_tranform.position.y, GetRadius());
    }

    void Actor::AddComponet(std::unique_ptr<Component> componet) {
        componet->SetOwner(this);
        m_componet.push_back(std::move(componet));
    }

}