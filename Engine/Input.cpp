#include "pch.h"
#include "Input.h"

#include <SDL3/SDL.h>

namespace nu {

	bool Input::Instantiate() {
		int numkeys;
		const bool* keyState = SDL_GetKeyboardState(&numkeys);
		m_keySates.resize(numkeys);

		std::copy(keyState, keyState + numkeys, m_keySates);

		return true; 
	}
	void Input::ShutDown() {
		
	};
	void Input::Update() {
		
	};
}