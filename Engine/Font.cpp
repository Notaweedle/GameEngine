#include "pch.h"
#include "Font.h"
#include <iostream>

namespace nu
{
	Font::~Font()
	{
		Close();
	}

	bool Font::Load(const std::string& path, int size)
	{
		m_font = TTF_OpenFont(path.c_str(), (float)size);
		if (m_font == nullptr)
		{
			std::cerr << "Failed to load font: " << path << std::endl;
			return false;
		}
		return true;
	}

	void Font::Close()
	{
		if (m_font)
		{
			TTF_CloseFont(m_font);
			m_font = nullptr;
		}
	}
}
