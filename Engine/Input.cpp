#include "pch.h"
#include "Input.h"

#include <SDL3/SDL.h>

namespace nu {

	bool Input::Instantiate() {
		int numkeys;
		const bool* keyState = SDL_GetKeyboardState(&numkeys);
		m_keySates.resize(numkeys);

		std::copy(keyState, keyState + numkeys, m_keySates.begin());

		return true; 
	}

	void Input::ShutDown() {
		//TODO put stuff here
	};

	void Input::Update() {
		m_preKeySates = m_keySates;
		m_preButtonSates = m_buttonSates;
		const bool* keyState = SDL_GetKeyboardState(nullptr);
		std::copy(keyState,keyState + m_keySates.size(), m_keySates.begin());
		m_buttonSates = SDL_GetMouseState(&m_mousePos.x, &m_mousePos.y);

	};

	uint32_t Input::GetButtonBit(MouseButton button) const
	{
		return SDL_BUTTON_MASK((uint32_t)button);
	}

}