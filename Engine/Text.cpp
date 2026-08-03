#include "pch.h"
#include "Text.h"
#include "Font.h"
#include "Renderer.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>

namespace nu
{
	Text::~Text()
	{
		Destroy();
	}

	void Text::Create(const Renderer& renderer, const std::string& text, const Font& font,
		Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		Destroy();

		SDL_Color color{ r, g, b, a };
		SDL_Surface* surface = TTF_RenderText_Blended(font.GetFont(), text.c_str(), 0, color);
		if (surface == nullptr)
		{
			std::cerr << "Failed to render text surface" << std::endl;
			return;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
		m_width = static_cast<float>(surface->w);
		m_height = static_cast<float>(surface->h);
		SDL_DestroySurface(surface);
	}

	void Text::Draw(const Renderer& renderer, float x, float y) const
	{
		if (m_texture == nullptr) return;

		SDL_FRect dest{ x, y, (float)m_width, (float)m_height };
		SDL_RenderTexture(renderer.GetRenderer(), m_texture, nullptr, &dest);
	}

	void Text::Destroy()
	{
		if (m_texture)
		{
			SDL_DestroyTexture(m_texture);
			m_texture = nullptr;
		}
	}
}
