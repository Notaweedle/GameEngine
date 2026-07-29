#pragma once

#include "Renderer.h"
#include "Vector2.h"
#include "Random.h"
#include "mathUitl.h"
#include "pch.h"
#include "SDL3/SDL.h"

#include <vector>
#include "Input.h"
#include "GameTime.h"
#include "Tranform.h"
#include "Actor.h"
#include "Model.h"
#include "Scene.h"
#include "Enemy.h"
#include "bullet.h"
#include "File.h"
#include "ParticleSystem.h"
#include "Audio.h"


namespace nu {
	class Engine {
	public:
		static Engine& Get() { static Engine engine; return engine; }
		bool Initialize();
		bool ShutDown();
		bool Update();
		Input& GetInput() { return m_input; };
		Renderer& GetRenderer() { return m_renderer; };
		Time& GetTime() { return m_time; };
		ParticleSystem& GetParticleSystem() { return m_particleSystem; };
		Audio& GetAudio() { return m_audio; };

		Engine(const Engine&) = delete;
		
	private:
		Engine() = default;
		Input m_input;
		Renderer m_renderer;
		Time m_time;
		ParticleSystem m_particleSystem{ 1000 };
		Audio m_audio;
	};

}