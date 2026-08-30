#pragma once
#include "RendererComponent.h"
#include "Resources/Resource.h"


namespace nu
{

	class SpriteAnimationComponent : public RendererComponent
	{
	public :
		CLASS_PROTOTYPE(SpriteAnimationComponent)

		void Draw(const Renderer& renderer) override;
		void Update(float dt) override;
		void Read(const json::value_t& value) override;

	private:
		float m_framesPerSec = 1.0f;
		bool m_loop = true;

		unsigned int m_frame = 0;
		float m_frameTimer = 0;
		res_t<class TextureFrames> m_textureFrames;



	};








}