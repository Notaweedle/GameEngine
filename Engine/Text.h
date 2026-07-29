#pragma once
#include <string>
#include <SDL3/SDL.h>

namespace nu
{
	class Font;
	class Renderer;

	class Text
	{
	public:
		Text() = default;
		~Text();

		void Create(const Renderer& renderer, const std::string& text, const Font& font,
			Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		void Draw(const Renderer& renderer, float x, float y) const;
		void Destroy();

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

	private:
		SDL_Texture* m_texture = nullptr;
		int m_width = 0;
		int m_height = 0;
	};
}
