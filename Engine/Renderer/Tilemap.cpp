#include "pch.h"
#include "Tilemap.h"
#include "Texture.h"
#include "Serialization/json.h"
#include "Resources/ResourceManager.h"
#include "Core/StringUtil.h"
#include <algorithm>
#include <climits>

namespace nu
{
	// Tiled stores flip/rotation flags in the top bits of a GID. Strip them
	// to get the real tile index. (0x80000000 H, 0x40000000 V, 0x20000000 D)
	static const unsigned int kGidFlagMask = 0x1FFFFFFFu;

	// Read a tile array ("data") from a layer or chunk object, masking flip flags.
	// GIDs of flipped tiles exceed INT_MAX, so they must be read as unsigned.
	static void ReadTileArray(const json::value_t& obj, std::vector<int>& out)
	{
		if (!obj.HasMember("data") || !obj["data"].IsArray()) return;
		const auto& arr = obj["data"].GetArray();
		out.clear();
		out.reserve(arr.Size());
		for (auto& e : arr)
		{
			unsigned int gid = e.IsUint() ? e.GetUint() : 0u;
			out.push_back((int)(gid & kGidFlagMask));
		}
	}

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

		// grab the tileset image (basename) to use as the default layer texture
		if (JSON_HAS_NAME(document, "tilesets") && JSON_GET_NAME(document, "tilesets").IsArray())
		{
			const auto& sets = JSON_GET_NAME(document, "tilesets").GetArray();
			if (sets.Size() > 0 && sets[0].HasMember("image") && sets[0]["image"].IsString())
			{
				std::string img = sets[0]["image"].GetString();
				size_t p = img.find_last_of("/\\");
				m_tilesetTextureName = (p == std::string::npos) ? img : img.substr(p + 1);
			}
		}
		if (!m_tilesetTextureName.empty())
			m_tilesetTexture = Resources().Get<Texture>(m_tilesetTextureName, renderer);

		// For infinite maps, every layer's chunks must share ONE origin/size or
		// the layers won't line up. Pre-scan all tile layers for global bounds.
		int gMinX = INT_MAX, gMinY = INT_MAX, gMaxX = INT_MIN, gMaxY = INT_MIN;
		bool anyChunks = false;
		if (JSON_HAS_NAME(document, "layers"))
		{
			for (auto& layerValue : JSON_GET_NAME(document, "layers").GetArray())
			{
				std::string type;
				JSON_READ_NAME(layerValue, "type", type);
				if (!EqualsIgnoreCase(type, "tilelayer")) continue;
				if (!JSON_HAS_NAME(layerValue, "chunks")) continue;

				for (auto& c : JSON_GET_NAME(layerValue, "chunks").GetArray())
				{
					int cx = 0, cy = 0, cw = 0, ch = 0;
					JSON_READ_NAME(c, "x", cx); JSON_READ_NAME(c, "y", cy);
					JSON_READ_NAME(c, "width", cw); JSON_READ_NAME(c, "height", ch);
					gMinX = std::min(gMinX, cx); gMinY = std::min(gMinY, cy);
					gMaxX = std::max(gMaxX, cx + cw); gMaxY = std::max(gMaxY, cy + ch);
					anyChunks = true;
				}
			}
		}
		int gW = anyChunks ? (gMaxX - gMinX) : 0;
		int gH = anyChunks ? (gMaxY - gMinY) : 0;

		// pixel offset of the grid origin (map coords -> assembled-grid coords)
		m_originX = anyChunks ? (float)(gMinX * m_tileWidth)  : 0.0f;
		m_originY = anyChunks ? (float)(gMinY * m_tileHeight) : 0.0f;

		// read tilemap layers
		if (JSON_HAS_NAME(document, "layers"))
		{
			for (auto& layerValue : JSON_GET_NAME(document, "layers").GetArray())
			{
				std::string type;
				JSON_READ_NAME(layerValue, "type", type);

				// object layer: collect tile objects (sprites placed in the editor)
				if (EqualsIgnoreCase(type, "objectgroup"))
				{
					if (JSON_HAS_NAME(layerValue, "objects"))
					{
						for (auto& objValue : JSON_GET_NAME(layerValue, "objects").GetArray())
						{
							// keep ALL objects: tile objects (with gid) carry art, while
							// rectangle/point objects are invisible triggers/markers (gid 0).
							TileObject obj;
							if (objValue.HasMember("gid"))
							{
								unsigned int gid = objValue["gid"].IsUint() ? objValue["gid"].GetUint() : 0u;
								obj.gid = (int)(gid & kGidFlagMask);
							}
							JSON_READ_NAME(objValue, "x", obj.x);
							JSON_READ_NAME(objValue, "y", obj.y);
							JSON_READ_NAME(objValue, "width", obj.width);
							JSON_READ_NAME(objValue, "height", obj.height);
							JSON_READ_NAME(objValue, "name", obj.name);
							m_objects.push_back(obj);
						}
					}
					continue;
				}

				// only tile layers have tile data (skip image layers, etc.)
				if (!EqualsIgnoreCase(type, "tilelayer")) continue;

				Layer layer;
				JSON_READ_NAME(layerValue, "width", layer.width);
				JSON_READ_NAME(layerValue, "height", layer.height);

				if (JSON_HAS_NAME(layerValue, "data"))
				{
					// finite map: one flat data array
					ReadTileArray(layerValue, layer.data);
				}
				else if (JSON_HAS_NAME(layerValue, "chunks"))
				{
					// infinite map: assemble chunks into a grid using the GLOBAL
					// origin/size so every layer lines up.
					layer.width = gW;
					layer.height = gH;
					layer.data.assign((size_t)gW * gH, 0);

					for (auto& c : JSON_GET_NAME(layerValue, "chunks").GetArray())
					{
						int cx = 0, cy = 0, cw = 0, ch = 0;
						JSON_READ_NAME(c, "x", cx); JSON_READ_NAME(c, "y", cy);
						JSON_READ_NAME(c, "width", cw); JSON_READ_NAME(c, "height", ch);

						std::vector<int> cd;
						ReadTileArray(c, cd);

						for (int yy = 0; yy < ch; yy++)
						{
							for (int xx = 0; xx < cw; xx++)
							{
								int si = yy * cw + xx;
								if (si >= (int)cd.size()) continue;
								int gx = (cx - gMinX) + xx;
								int gy = (cy - gMinY) + yy;
								if (gx < 0 || gy < 0 || gx >= gW || gy >= gH) continue;
								layer.data[(size_t)gy * gW + gx] = cd[si];
							}
						}
					}
				}

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

				// no per-layer texture set? fall back to the map's tileset image
				if (!layer.texture && !m_tilesetTextureName.empty())
				{
					layer.texture = Resources().Get<Texture>(m_tilesetTextureName, renderer);
					if (!layer.texture)
						std::cerr << "Could not read tileset texture " << m_tilesetTextureName << std::endl;
				}

				m_layers.push_back(std::move(layer));
			}
		}

		return true;
	}

	// source rectangle in the tileset texture for a given tile id (Tiled gid, 1-based)
	Rect Tilemap::GetTileRect(const Layer& layer, int tileId)
	{
		tileId = (int)((unsigned int)tileId & kGidFlagMask);   // strip flip flags
		if (tileId == 0 || !layer.texture) return Rect();      // 0 = empty tile

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

	// source rectangle in the tileset texture for any gid (used for object sprites
	// and for pulling a single tile out of the map). Strips flip flags.
	Rect Tilemap::GetGidRect(int gid)
	{
		gid = (int)((unsigned int)gid & kGidFlagMask);
		if (gid == 0 || !m_tilesetTexture) return Rect();

		Vector2 textureSize = m_tilesetTexture->GetSize();
		int tilesPerRow = (m_tileWidth > 0) ? (int)(textureSize.x / m_tileWidth) : 1;
		if (tilesPerRow <= 0) tilesPerRow = 1;

		int column = (gid - 1) % tilesPerRow;
		int row    = (gid - 1) / tilesPerRow;

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
