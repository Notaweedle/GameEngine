#include "pch.h"
#include "Tilemap.h"
#include "Texture.h"
#include "Serialization/json.h"
#include "Resources/ResourceManager.h"
#include "Core/StringUtil.h"

namespace nu
{
	bool Tilemap::Load(const std::string& filename, class Renderer& renderer)
	{
		// load json
		json::document_t document;
		if (!json::Load(filename, document))
		{
			std::cerr << "Could not load Tilemap " << filename << std::endl;
			return false;
		}

		// read tilemap tile size
		JSON_READ_NAME(document, "tilewidth", m_tileWidth);
		JSON_READ_NAME(document, "tileheight", m_tileHeight);

		// read tilemap layers
		if (JSON_HAS_NAME(document, "layers"))
		{
			for (auto& layerValue : JSON_GET_NAME(document, "layers").GetArray())
			{
				// only tile layers have tile data (skip object/image layers)
				std::string type;
				JSON_READ_NAME(layerValue, "type", type);
				if (!EqualsIgnoreCase(type, "tilelayer")) continue;

				Layer layer;
				JSON_READ_NAME(layerValue, "width", layer.width);
				JSON_READ_NAME(layerValue, "height", layer.height);
				JSON_READ_NAME(layerValue, "data", layer.data);

				// read layer custom properties (Tiled: layer -> Properties)
				if (JSON_HAS_NAME(layerValue, "properties"))
				{
					for (auto& propertyValue : JSON_GET_NAME(layerValue, "properties").GetArray())
					{
						std::string name;
						JSON_READ_NAME(propertyValue, "name", name);

						if (EqualsIgnoreCase(name, "texture_name"))
						{
							std::string value;
							JSON_READ_NAME(propertyValue, "value", value);

							layer.texture = Resources().Get<Texture>(value, renderer);
							if (!layer.texture)
								std::cerr << "Could not read tilemap layer texture " << value << std::endl;
						}
						else if (EqualsIgnoreCase(name, "has_collision"))
						{
							JSON_READ_NAME(propertyValue, "value", layer.hasCollision);
						}
					}
				}

				m_layers.push_back(std::move(layer));
			}
		}

		return true;
	}

	// source rectangle in the tileset texture for a given tile id (Tiled gid, 1-based)
	Rect Tilemap::GetTileRect(const Layer& layer, int tileId)
	{
		if (tileId == 0 || !layer.texture) return Rect();   // 0 = empty tile

		Vector2 textureSize = layer.texture->GetSize();
		int tilesPerRow = (m_tileWidth > 0) ? (int)(textureSize.x / m_tileWidth) : 1;
		if (tilesPerRow <= 0) tilesPerRow = 1;

		int column = (tileId - 1) % tilesPerRow;
		int row    = (tileId - 1) / tilesPerRow;

		return Rect{
			(float)(column * m_tileWidth),
			(float)(row * m_tileHeight),
			(float)(m_tileWidth),
			(float)(m_tileHeight)
		};
	}

	// world (pixel) position of a tile given its index into the layer data (row-major)
	Vector2 Tilemap::GetTilePosition(const Layer& layer, int tileIndex)
	{
		int column = tileIndex % layer.width;
		int row    = tileIndex / layer.width;

		return Vector2{ (float)(column * m_tileWidth), (float)(row * m_tileHeight) };
	}
}
