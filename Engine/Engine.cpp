// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework/framework.h"
#include "Engine.h"
#include "Input/Input.h"
#include <iostream>



namespace nu {
	

	bool Engine::Initialize() {
		
		
		m_renderer.Initialize("Astroid", 1280, 800);
		m_renderer.SetColor(0.0f,0.0f,0.0f);
		m_input.Initialize();
		m_audio.Initialize();
		m_physics.Initialize();

		return true;
	};
	bool Engine::ShutDown() {
		m_audio.ShutDown();
		m_input.ShutDown();
		m_renderer.ShutDown();

		return true;
	};

	bool Engine::Update() {
		
		m_time.Tick();
		m_input.Update();

		return true;
	};
}