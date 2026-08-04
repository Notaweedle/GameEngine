#pragma once
#include <string>
#include "Vector2.h"
struct SDL_Texture;

namespace nu
{
	class Renderer;   
	class Texture
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
