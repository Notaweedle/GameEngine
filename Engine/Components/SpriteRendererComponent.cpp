#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include <Serialization/json.h>




namespace nu {

    FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer)
	{
        if (m_texture == nullptr) {
            std::cout << "m_texture can NOT be null" << std::endl;
            return; 
        }
        if (m_texture) { 
            renderer.DrawTexture(
                m_texture.get(),
                GetOwner()->getTransform().position.x,
                GetOwner()->getTransform().position.y,
                GetOwner()->getTransform().rotation,
                GetOwner()->getTransform().scale);
        }
            
    }

    void SpriteRendererComponent::Read(const json::value_t& value)
    {
        RendererComponent::Read(value);

        std::string textureName;
        JSON_READ_NAME(value, "texture", textureName);
        if (!textureName.empty())
        {
            m_texture = Resources().Get<Texture>(textureName, Engine::Get().GetRenderer());
        }
    
	}

}



