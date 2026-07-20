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
#include "Secne.h"

namespace nu {
	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		bool ShutDown();
		bool Update();
		Input& GetInput() { return m_input; };
		Renderer& GetRenderer() { return m_renderer; };
		Time& GetTime() { return m_time; };
	private:
		Input m_input;
		Renderer m_renderer;
		Time m_time;
	};

	extern Engine engine;

}