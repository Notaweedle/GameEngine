 #include "pch.h"
#include "TextureFrames.h"
#include "Serialization/json.h"
#include "Texture.h"
#include <Resources/ResourceManager.h>



namespace nu {

	bool TextureFrames::Load(const std::string& fileName, class Renderer& renderer )
	{
		json::document_t doc;

		if (!json::Load(fileName, doc)) 
		{
			std::cerr << "Could not load Texture Frames: " << fileName << std::endl;
			return false;
		}

		std::string texture_name;
		JSON_READ(doc, texture_name);   // reads the "texture_name" key
		if(texture_name.empty()){
			return false;
		}

		m_texture = Resources().Get<Texture>(texture_name, renderer);
		if (!m_texture) {
			std::cerr << "Could not load Texture Frame texture: " << fileName << std::endl;
			return false;
		}

		JSON_READ_NAME(doc, "columns", m_numColumns);
		JSON_READ_NAME(doc, "rows", m_numRows);
		JSON_READ_NAME(doc, "start_frame", m_startFrame);
		JSON_READ_NAME(doc, "total_frame", m_totalFrame);

		if(m_numColumns <= 0 || m_numRows <= 0){
			std::cerr << "Could not load Texture Frame texture: " << fileName << std::endl;
			return false;
			
		}

		Vector2 textureSize = m_texture->GetSize();
		m_FrameSize = textureSize / Vector2{static_cast<float> (m_numColumns) ,static_cast<float> (m_numRows) };


		return true;
	}

	Rect TextureFrames::GetFrameRect(unsigned int frame)
	{
		if (frame < 0 || frame >= m_totalFrame) {
			std::cerr << "Could not load Texture out of Bounds: " << frame <<"is out of bounds." << std::endl;
			frame = 0;
		}


		int currentFrame = m_startFrame + frame;
		int column = currentFrame % m_numColumns;
		int row = currentFrame / m_numColumns;

		float x = column * m_FrameSize.x;
		float y = row * m_FrameSize.y;



		return Rect{
			x,y,
			m_FrameSize.x,
			m_FrameSize.y
		};
	}



}