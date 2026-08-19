#include "pch.h"
#include "SpriteRendererComponent.h"
#include "Renderer.h"
#include "Actor.h"
#include "Engine.h"




namespace nu {

    /*FACTORY_REGISTER(SpriteRendererComponent)

	void SpriteRendererComponent::Draw(const Renderer& renderer)
	{
        if(m_texture)
        renderer.DrawTexture(m_texture.get(),
                    GetOwner()-> GetTranform().position.x;
                    GetOwner()-> GetTranform().position.y,
                    GetOwner()-> GetTranform().rotation,
                    GetOwner()-> GetTranform().scale);
            
       	}

	void SpriteRendererComponent::Read(const json::value_t& value)
	{
        Read(value);

        std::string textureName;
        JSON_READ_NAME(value, "texture", textureName);
        if (!textureName.empty()) 
        {
            m_texture = Resource().Get()<Texture>(textureName, Engine::Get().GetRenderer());
        }

        JSON_READ_NAME(value, "tag" , Actor::getTag);
        JSON_READ_NAME(value, "lifespan" , Actor::getLifeSpan);
        JSON_READ_NAME(value, "velocity" , Actor::getVelocity);
        JSON_READ_NAME(value, "damping" , Actor::get);


        if (JSON_READ_NAME(value, "component")) 
        {
            for (auto& ComponentValue : JSON_GET_NAME(value, "componets").getArray()) 
            {
            
            }
        
        }

	}*/

}



