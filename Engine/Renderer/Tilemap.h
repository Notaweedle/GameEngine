#pragma once
#include "Resources/Resource.h"
#include <vector>
#include <string>
#include <Math/Rect.h>
#include <Math/Vector2.h>
namespace nu
{
	class Tilemap : public Resource
	{
	public:
		struct Layer
		{
			int width{ 0 };
			int height{ 0 };
			bool hasCollision{ false };
			std::vector<int> data;
			res_t<class Texture> texture;
		};

		// a single sprite placed in a Tiled object layer (a "tile object")
		struct TileObject
		{
			int   gid{ 0 };                 // which tile in the tileset
			float x{ 0.0f }, y{ 0.0f };     // bottom-left corner, in map pixels
			float width{ 0.0f }, height{ 0.0f };
			std::string name;               // Tiled object name (for game spawning)
		};

	public:

		bool Load(const std::string& filename, class Renderer& renderer);

		const std::vector<Layer>& GetLayers() const { return m_layers; }
		Rect GetTileRect(const Layer& layer, int tileId);
		Vector2 GetTilePosition(const Layer& layer, int tileIndex);

		int GetTileWidth() const { return m_tileWidth; }
		int GetTileHeight() const { return m_tileHeight; }

		// object-layer sprites, and helpers to pull a single tile out of the tileset
		const std::vector<TileObject>& GetObjects() const { return m_objects; }
		res_t<class Texture> GetTilesetTexture() const { return m_tilesetTexture; }
		Rect GetGidRect(int gid);                 // source rect in the tileset for a gid

		// pixel offset of the assembled grid origin (for converting map coords)
		float GetOriginX() const { return m_originX; }
		float GetOriginY() const { return m_originY; }

	private:
		int m_tileWidth{ 0 };
		int m_tileHeight{ 0 };

		// tileset image (basename) read from the map's "tilesets" array; used
		// as the layer texture when a layer has no texture_name property.
		std::string m_tilesetTextureName;
		res_t<class Texture> m_tilesetTexture;

		float m_originX{ 0.0f };
		float m_originY{ 0.0f };

		std::vector<Layer> m_layers;
		std::vector<TileObject> m_objects;
	};
}
