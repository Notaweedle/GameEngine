#include "pch.h"
#include "TilemapRendererComponent.h"
#include "Renderer/Tilemap.h"
#include "Renderer/Texture.h"
#include "Framework/Actor.h"
#include "Engine.h"
#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Physics/Physics.h"

namespace nu
{
	FACTORY_REGISTER(TilemapRendererComponent)

	// copy the tilemap reference for cloning; physics bodies are rebuilt in Start()
	TilemapRendererComponent::TilemapRendererComponent(const TilemapRendererComponent& other)
		: m_tilemapName{ other.m_tilemapName }
		, m_tilemap{ other.m_tilemap }
	{
	}

	void TilemapRendererComponent::Start()
	{
		if (!m_tilemap) return;

		const Transform& t = GetOwner()->getTransform();
		const float scale = t.scale;
		const float tw = (float)m_tilemap->GetTileWidth();
		const float th = (float)m_tilemap->GetTileHeight();

		// build a static physics body for every solid tile in a collision layer
		for (const auto& layer : m_tilemap->GetLayers())
		{
			if (!layer.hasCollision) continue;

			for (size_t i = 0; i < layer.data.size(); i++)
			{
				if (layer.data[i] == 0) continue;

				Vector2 pos = m_tilemap->GetTilePosition(layer, (int)i);

				Transform tileTransform;
				tileTransform.position = {
					t.position.x + (pos.x + tw * 0.5f) * scale,
					t.position.y + (pos.y + th * 0.5f) * scale
				};
				tileTransform.rotation = 0.0f;
				tileTransform.scale = scale;

				PhysicsBody::PhysicsBodyDef def;
				def.isDynamic = false;                 // tiles are static world geometry
				def.shape = PhysicsBody::Shape::Box;
				def.actor = GetOwner();

				m_physicsBodies.push_back(std::make_unique<PhysicsBody>(
					tileTransform, Vector2{ tw, th }, def, Engine::Get().GetPhysics()));
			}
		}
	}

	void TilemapRendererComponent::Draw(const Renderer& renderer)
	{
		if (!m_tilemap) return;

		const Transform& t = GetOwner()->getTransform();
		const float scale = t.scale;
		const float tw = (float)m_tilemap->GetTileWidth();
		const float th = (float)m_tilemap->GetTileHeight();

		for (const auto& layer : m_tilemap->GetLayers())
		{
			if (!layer.texture) continue;

			for (size_t i = 0; i < layer.data.size(); i++)
			{
				int tileId = layer.data[i];
				if (tileId == 0) continue;   // empty tile

				Rect    source = m_tilemap->GetTileRect(layer, tileId);
				Vector2 pos    = m_tilemap->GetTilePosition(layer, (int)i);

				// DrawTexture centers on (x,y); offset by half a tile so tiles align to a grid
				float cx = t.position.x + (pos.x + tw * 0.5f) * scale;
				float cy = t.position.y + (pos.y + th * 0.5f) * scale;

				renderer.DrawTexture(*layer.texture, source, cx, cy, 0.0f, scale, false);
			}
		}
	}

	void TilemapRendererComponent::Read(const json::value_t& value)
	{
		RendererComponent::Read(value);

		JSON_READ_NAME(value, "tilemap", m_tilemapName);
		if (!m_tilemapName.empty())
			m_tilemap = Resources().Get<Tilemap>(m_tilemapName, Engine::Get().GetRenderer());
	}
}
