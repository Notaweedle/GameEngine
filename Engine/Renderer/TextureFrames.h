#pragma once
#include "Resource.h"
#include <string>
#include <Math/Vector2.h>
#include <Math/Rect.h>
namespace nu 
{

	class TextureFrames : public Resource
	{
	public:
		bool Load(const std::string& fileName, class Renderer& renderere);
		Rect GetFrameRect(unsigned int frame);


	private:
		int m_numColumns = 0;
		int m_numRows = 0;
		int m_startFrame = 0;
		int m_totalFrame = 0;

		Vector2 m_FrameSize{ 0.f,0.f };
		res_t <class Texture> m_texture;
	};

}