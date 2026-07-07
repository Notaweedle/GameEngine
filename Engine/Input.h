#pragma once
#include <vector>
#include "Vector2.h"
namespace nu {
	class Input {
	public:
		bool Instantiate();
		void ShutDown();
		void Update();

	private:

		std::vector<bool> m_keySates;
		std::vector<bool> m_preKeySates;
		
		uint32_t m_buttonSates;
		uint32_t m_preButtonSates;


		Vector2 m_mousePos;

	};
	
		
}