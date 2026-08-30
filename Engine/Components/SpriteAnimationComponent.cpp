#include "pch.h"
#include "SpriteAnimationComponent.h"
#include "Renderer/Renderer.h" 
#include "Framework/Actor.h" 
#include "Resources/ResourceManager.h"
#include "Renderer/TextureFrames.h"
#include "Core/Factory.h"
#include "Engine.h"


namespace nu {


	FACTORY_REGISTER(SpriteAnimationComponent)

	void SpriteAnimationComponent::Update(float dt)
	{
		if (!m_textureFrames || m_textureFrames->GetTotalFrames() == 0) return;

		m_frameTimer += dt;
		float frameTime = 1.0f / m_framesPerSec;
		if (m_frameTimer >= frameTime) {
			m_frameTimer -= frameTime;                 // reset the accumulator so we step ~once per frameTime
			m_frame = (m_frame + 1) % m_textureFrames->GetTotalFrames();
		}
		


	}

	void SpriteAnimationComponent::Draw(const Renderer& renderer)
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

	void SpriteAnimationComponent::Read(const json::value_t& value)
	{

		RendererComponent::Read(value);

		JSON_READ_NAME_REQ(value, "frames_per_second", m_framesPerSec);
		JSON_READ_NAME(value, "loop", m_loop);

		std::string texture_frames;

		JSON_READ_REQ(value, texture_frames);  

		if(!texture_frames.empty()){
			m_textureFrames = Resources().Get<TextureFrames>(texture_frames, Engine::Get().GetRenderer());
		}

	}




}

