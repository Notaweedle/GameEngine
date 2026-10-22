#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include <Serialization/json.h>




namespace nu {

    FACTORY_REGISTER(SpriteRendererComponent)

        void SpriteRendererComponent::Start()
        {
            if (!m_textureName.empty()){
                m_texture = Resources().Get<Texture>(m_textureName, Engine::Get().GetRenderer());
                if (m_texture) {
                    m_size = m_texture.get()->GetSize();
                }
            }
        }

    void SpriteRendererComponent::Draw(const Renderer& renderer)
	{
        if (m_texture == nullptr) {
            std::cout << "m_texture can NOT be null" << std::endl;
            return; 
        }
        if (m_texture) { 
            if (m_sourceRect.w > 0 && m_sourceRect.h > 0) {
                renderer.DrawTexture(
                    m_texture.get(),
                    m_sourceRect,
                    GetOwner()->getTransform().position.x,
                    GetOwner()->getTransform().position.y,
                    GetOwner()->getTransform().rotation,
                    GetOwner()->getTransform().scale,
                    m_flipH);
            }
            else {
                renderer.DrawTexture(
                    m_texture.get(),
                    GetOwner()->getTransform().position.x,
                    GetOwner()->getTransform().position.y,
                    GetOwner()->getTransform().rotation,
                    GetOwner()->getTransform().scale,
                    m_flipH);
            }
        }
            
    }

    void SpriteRendererComponent::Read(const json::value_t& value)
    {
        RendererComponent::Read(value);

        JSON_READ_NAME(value, "texture", m_textureName);
        JSON_READ_NAME(value, "flipH", m_flipH);
        
    
	}

}



