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
		
		


	}

	void SpriteAnimationRendererComponent::Draw(const Renderer& renderer)
	{
		if (!m_textureFrames) return;


		auto transform = GetOwner()->getTransform();


			renderer.DrawTexture(
			*m_textureFrames->GetTexture(),
			m_textureFrames->GetFrameRect(m_frame),
			transform.position.x,
			transform.position.y,
			transform.rotation,
			transform.scale,
			false);
	}

	void SpriteAnimationRendererComponent::Read(const json::value_t& value)
	{

		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "frames_per_second", m_framesPerSec);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;

		JSON_READ_REQ(value, texture_frames);  

		if(!texture_frames.empty()){
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
			if (!m_textureFrames) {
				std::cerr << "Could not load texture frame: " << texture_frames << std::endl;
			}

		}




	}




}

