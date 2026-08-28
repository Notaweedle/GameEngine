#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"
#include "Serialization/json.h"
namespace nu 
{
	class SpriteRendererComponent : public RendererComponent 
	{
	public :
		CLASS_PROTOTYPE(SpriteRendererComponent);


		void Draw(const Renderer& renderer) override;

		void Read(const json::value_t& value) override;


	protected:
	
		res_t<Texture> m_texture;
	};
}