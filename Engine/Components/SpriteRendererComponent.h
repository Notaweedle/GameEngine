#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "Renderer/Texture.h"
#include "Serialization/json.h"
#include <Math/Rect.h>
namespace nu 
{
	class SpriteRendererComponent : public RendererComponent 
	{
	public :
		CLASS_PROTOTYPE(SpriteRendererComponent);

		void Start() override;
		void Draw(const Renderer& renderer) override;

		const Vector2& getSize() const { return m_size; }
		bool getFilpH() { return m_flipH; }
		void setFilpH(bool flip = true) { m_flipH = flip; }

		void Read(const json::value_t& value) override;


	protected:
		std::string m_textureName;
		Rect m_sourceRect;
		Vector2 m_size{ 0.0f,0.0f };
		bool m_flipH{ false };


		res_t<Texture> m_texture;
	};
}