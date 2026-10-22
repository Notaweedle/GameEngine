#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"
#include "SpriteRendererComponent.h"


namespace nu
{

	class SpriteAnimationRendererComponent : public SpriteRendererComponent
	{
	public :
		CLASS_PROTOTYPE(SpriteAnimationRendererComponent)


		void Start() override;
		void Update(float dt) override;
		void Read(const json::value_t& value) override;

	private:
		std::string m_textureFramesName;
		float m_framesPerSec = 1.0f;
		bool m_loop = true;
		unsigned int m_frame = 0;
		float m_frameTimer = 0;
		res_t<class TextureFrames> m_textureFrames;



	};








}