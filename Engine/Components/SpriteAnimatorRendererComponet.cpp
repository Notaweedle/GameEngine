#include "pch.h"
#include "SpriteAnimatorRendererComponet.h"
#include "core/StringUtil.h"
#include "core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureFrames.h"
#include "Engine.h"


namespace nu {

	FACTORY_REGISTER(SpriteAnimatorRendererComponet)

	void SpriteAnimatorRendererComponet::Start()
	{
		if (!m_defaultAnimationName.empty()) {
			Play(m_defaultAnimationName);
		}
		else if (!m_animations.empty()) {
			Play(m_animations.begin()->first);
		}
	}

	void SpriteAnimatorRendererComponet::Update(float dt)
	{
		if (m_pause || !m_currentAnimation.textureFrames || m_currentAnimation.textureFrames->GetTotalFrames() == 0) return;

		m_frameTimer += dt;
		float frameTime = 1.0f / m_currentAnimation.fps;   // seconds each frame is shown

		// advance one frame for every frameTime that has elapsed
		while (m_frameTimer >= frameTime) {
			m_frameTimer -= frameTime;
			m_frame++;

			if (m_frame >= m_currentAnimation.textureFrames->GetTotalFrames()) {
				m_frame = m_currentAnimation.loop ? 0u : m_currentAnimation.textureFrames->GetTotalFrames() - 1;
			}
		}

		m_sourceRect = m_currentAnimation.textureFrames->GetFrameRect(m_frame);
	}

	void SpriteAnimatorRendererComponet::Play(const std::string& name)
	{
		auto iter = m_animations.find(ToLower(name));
		if (iter == m_animations.end()) {
			std::cerr << "could not find animation name : " << name << std::endl;
			return;
		}
		m_currentAnimation = iter->second;

		m_frame = 0;
		m_frameTimer = 0.0f;

		if (m_currentAnimation.textureFrames) {
			m_texture = m_currentAnimation.textureFrames->GetTexture();
			m_sourceRect = m_currentAnimation.textureFrames->GetFrameRect(m_frame);
			m_size = Vector2{ m_sourceRect.w, m_sourceRect.h };
		}
	}

	void SpriteAnimatorRendererComponet::Read(const json::value_t& value)
	{
		SpriteRendererComponent::Read(value);

		JSON_READ_NAME(value, "default_animation", m_defaultAnimationName);

		if (JSON_HAS_NAME(value, "animations") && JSON_GET_NAME(value, "animations").IsArray())
		{
			for (auto& animatorValue : JSON_GET_NAME(value, "animations").GetArray())
			{
				SpriteAnimation spriteAnimation;

				JSON_READ_NAME(animatorValue, "name", spriteAnimation.name);

				std::string textureFramesName;
				JSON_READ_NAME_REQ(animatorValue, "texture_frames", textureFramesName);

				if (!textureFramesName.empty())
				{
					spriteAnimation.textureFrames = Resources().Get<TextureFrames>(textureFramesName, Engine::Get().GetRenderer());
					if (!spriteAnimation.textureFrames)
					{
						std::cerr << "Could not load texture frames: " << textureFramesName << std::endl;
					}
				}

				JSON_READ_NAME_REQ(animatorValue, "frames_per_second", spriteAnimation.fps);
				JSON_READ_NAME(animatorValue, "loop", spriteAnimation.loop);

				m_animations[ToLower(spriteAnimation.name)] = spriteAnimation;
			}
		}
	}
}
