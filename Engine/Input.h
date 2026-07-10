#pragma once
#include <vector>
#include "Vector2.h"
namespace nu {
	class Input {

	public:
		enum class MouseButton {
			Left = 1,
			Middle=2,
			Right=3,
		};

	public:
		bool Instantiate();
		void ShutDown();
		void Update();

		bool GetKeyDown(int key) const { return m_keySates[key]; }
		bool GetPreKeyDown(int key) const { return m_preKeySates[key]; }
		bool GetPreKeyPressed(int key) const { return !m_preKeySates[key]; }
		bool GetKeyRelased(int key) const { return m_keySates[key]; }

		const Vector2& GetMousePosition() const { return m_mousePos; }

		bool GetButtonDown(MouseButton button) const { return m_buttonSates & GetButtonBit(button); }
		bool GetPrevButtonDown(MouseButton button) const { return m_preButtonSates & GetButtonBit(button); }
		bool GetButtonPressed(MouseButton button) const { return GetButtonDown(button) && !GetPrevButtonDown(button); }
		bool GetButtonReleased(MouseButton button) const { return !GetButtonDown(button) && GetPrevButtonDown(button); }




	private:
		uint32_t GetButtonBit(MouseButton button) const;
		std::vector<bool> m_keySates;
		std::vector<bool> m_preKeySates;
		
		uint32_t m_buttonSates=0;
		uint32_t m_preButtonSates=0;

		Vector2 m_mousePos;


	};
	
		
}