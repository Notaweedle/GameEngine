#pragma once
#include <string>
#include "Math/Vector2.h"
#include "Resource.h"
struct SDL_Texture;

namespace nu
{
	class Renderer; 

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, Renderer& renderer);

		Vector2 GetSize();

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}
