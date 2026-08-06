#pragma once
#include <string>
#include <SDL3/SDL.h>
#include "Resource.h"   // res_t
#include "Color.h"      // Color

namespace nu
{
	class Renderer;
	class Font;

	class Text
	{
	public:
		Text() = default;
		Text(res_t<Font> font) : m_font{ font } {}
		~Text();

		void SetFont(res_t<Font> font) { m_font = font; }

		bool Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(const Renderer& renderer, float x, float y);
		void Destroy();

		float GetWidth() const { return m_width; }
		float GetHeight() const { return m_height; }

	private:
		float m_width = 0;
		float m_height = 0;
		res_t<Font> m_font;
		SDL_Texture* m_texture{ nullptr };
	};
}
