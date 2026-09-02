#include "pch.h"
#include "SpriteAnimationRendererComponent.h"
#include "Renderer/Renderer.h" 
#include "Framework/Actor.h" 
#include "Math/mathUitl.h" 
#include "Resources/ResourceManager.h"
#include "Renderer/TextureFrames.h"
#include "Core/Factory.h"
#include "Engine.h"


namespace nu {


	FACTORY_REGISTER(SpriteAnimationRendererComponent)

	void SpriteAnimationRendererComponent::Update(float dt)
	{
		if (!m_textureFrames || m_textureFrames->GetTotalFrames() == 0) return;

		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSec;   // seconds each frame is shown

		// advance one frame for every frameTime that has elapsed
		while (m_frameTimer >= frameTime) {
			m_frameTimer -= frameTime;
			m_frame++;

			if (m_frame >= m_textureFrames->GetTotalFrames()) {
				m_frame = m_loop ? 0u : m_textureFrames->GetTotalFrames() - 1;
			}
		}
		
		m_sourceRect = m_textureFrames->GetFrameRect(m_frame);


	}

	void SpriteAnimationRendererComponent::Start()
	{

	}

	

	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{

		SpriteRendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "frames_per_second", m_framesPerSec);
		JSON_READ_NAME(value, "loop", m_loop);
		JSON_READ_NAME_REQ(value, "texture_frames", m_textureFramesName);

		// load the frames AFTER the name has been read from JSON
		if (!m_textureFramesName.empty()) {
			m_textureFrames = Resources().Get<TextureFrames>(m_textureFramesName, Engine::Get().GetRenderer());
			if (m_textureFrames) {

				m_sourceRect = m_textureFrames->GetFrameRect(0);
				m_size = Vector2{ m_sourceRect.w,m_sourceRect.h };
				m_texture = m_textureFrames->GetTexture();
			}
			if (!m_textureFrames) {
				std::cerr << "Could not load texture frame: " << m_textureFramesName << std::endl;
			}

		}

		




	}




}

