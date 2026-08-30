// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework/framework.h"
#include "Engine.h"
#include "Input/Input.h"
#include <iostream>



namespace nu {
	

	bool Engine::Initialize() {
		
		
		// physical window is 1280x800 (a quarter of the pixels of 2560x1600);
		// the renderer's logical presentation maps the 2560x1600 world onto it.
		m_renderer.Initialize("Astroid", 1280, 800);
		m_renderer.SetColor(0.0f,0.0f,0.0f);
		m_input.Initialize();
		m_audio.Initialize();

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