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

		// draw a specific texture + sub-rect directly (e.g. a single tile pulled
		// from a tilemap). Clears the texture name so Start() won't overwrite it.
		void SetTile(res_t<Texture> texture, const Rect& source)
		{
			m_texture = texture;
			m_sourceRect = source;
			m_size = Vector2{ source.w, source.h };
			m_textureName.clear();
		}

		void Read(const json::value_t& value) override;


	protected:
		std::string m_textureName;
		Rect m_sourceRect;
		Vector2 m_size{ 0.0f,0.0f };
		bool m_flipH{ false };


		res_t<Texture> m_texture;
	};
}