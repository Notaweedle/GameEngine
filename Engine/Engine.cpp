// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Engine.h"
#include "Input.h"
#include <Iostream>



namespace nu {
	

	bool Engine::Initialize() {
		
		
		m_renderer.Initialize("Game Engine", 1280, 1024);
		m_renderer.SetColor(0.0f,0.0f,0.0f);
		m_input.Initialize();

		return true;
	};
	bool Engine::ShutDown() {
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