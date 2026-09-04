#pragma once
#include "SpriteRendererComponent.h"
#include "Resources/ResourceManager.h"
#include <map>
#include <string>

namespace nu {
	class SpriteAnimatorRendererComponet : public SpriteRendererComponent
	{

	public :

		CLASS_PROTOTYPE(SpriteAnimatorRendererComponet)

		struct SpriteAnimation
		{
			std::string name;
			float fps{ 10.0f };
			bool loop = true;
			res_t<class TextureFrames> textureFrames;
		};

		void Start() override;
		void Update(float dt) override;
		void Play(const std::string& name);
		void Read(const json::value_t& value) override;

		bool getPasue() { return m_pause; }
		void setPasue(bool pause) { m_pause = pause; }
	private:
		unsigned int m_frame = 0;
		float m_frameTimer = 0;
		bool m_pause{ false };

		std::string m_defaultAnimationName;
		std::string m_currentAnimationName;
		SpriteAnimation m_currentAnimation;
		std::map<std::string, SpriteAnimation> m_animations;
	};
}
