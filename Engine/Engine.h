#pragma once

#include "pch.h"


#include "Core/Random.h"
#include "Core/Factory.h"
#include "Core/Singleton.h"
#include "Core/StringUtil.h"
#include "Core/GameTime.h"
#include "Core/File.h"
#include "Core/Enemy.h"
#include "Core/bullet.h"

#include "Math/mathUitl.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"


#include "Framework/Actor.h"
#include "Framework/Scene.h"


#include "Audio/Audio.h"

#include "Resources/ResourceManager.h"
#include "Resources/Resource.h"

#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"

#include "Input/Input.h"

#include "SDL3/SDL.h"
#include <vector>

namespace nu {
	class Engine {
	public:
		static Engine& Get() { return s_instance; }
		bool Initialize();
		bool ShutDown();
		bool Update();
		Input& GetInput() { return m_input; };
		Renderer& GetRenderer() { return m_renderer; };
		Time& GetTime() { return m_time; };
		ParticleSystem& GetParticleSystem() { return m_particleSystem; };
		Audio& GetAudio() { return m_audio; };

		
		
	private:
		Engine() = default;
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		ParticleSystem m_particleSystem{ 5000 };
		Audio m_audio;
		static Engine s_instance;
	};

	inline Engine Engine::s_instance;

}