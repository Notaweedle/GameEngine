#pragma once
#include <vector>
#include <string>
#include <memory>
#include <Renderer/Renderer.h>
#include <Components/RendererComponent.h>
#include <Resources/Resource.h>

namespace nu
{
	class TilemapRendererComponent : public RendererComponent
	{
	public:
		TilemapRendererComponent() = default;
		TilemapRendererComponent(const TilemapRendererComponent& other);

		CLASS_PROTOTYPE(TilemapRendererComponent)

			void Start() override;
		void Draw(const Renderer& renderer) override;

		void Read(const json::value_t& value) override;

	private:
		std::string m_tilemapName;
		res_t<class Tilemap> m_tilemap;

		std::vector<std::unique_ptr<class PhysicsBody>> m_physicsBodies;
	};
}
