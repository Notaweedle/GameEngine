#pragma once
#include <string>
#include "Resource.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace nu
{
	class Font : public Resource
	{
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& path, int size);
		void Close();

		TTF_Font* GetFont() const { return m_font; }

	private:
		TTF_Font* m_font = nullptr;
	};
}
