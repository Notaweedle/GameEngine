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

	bool Text::Create(Renderer& renderer, const std::string& text, const Color& color)
	{
		Destroy();

		if (m_font == nullptr || m_font->GetFont() == nullptr)
		{
			std::cerr << "Text::Create - no valid font set (font missing or failed to load)" << std::endl;
			return false;
		}

		
		SDL_Color sdlColor{
			static_cast<Uint8>(color.r * 255.0f),
			static_cast<Uint8>(color.g * 255.0f),
			static_cast<Uint8>(color.b * 255.0f),
			static_cast<Uint8>(color.a * 255.0f)
		};

		SDL_Surface* surface = TTF_RenderText_Blended(m_font->GetFont(), text.c_str(), 0, sdlColor);
		if (surface == nullptr)
		{
			std::cerr << "Failed to render text surface: " << SDL_GetError() << std::endl;
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.GetRenderer(), surface);
		m_width  = static_cast<float>(surface->w);
		m_height = static_cast<float>(surface->h);
		SDL_DestroySurface(surface);

		if (m_texture == nullptr)
		{
			std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}

	void Text::Draw(const Renderer& renderer, float x, float y)
	{
		if (m_texture == nullptr) return;

		SDL_FRect dest{ x, y, m_width, m_height };
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
