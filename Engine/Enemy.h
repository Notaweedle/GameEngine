#pragma once 
#include "Actor.h"
#include "Model.h"
namespace nu {
	class Enemy : public nu::Actor {
	public:
		Enemy() = default;
		Enemy(float speed, const nu::Tranform& tranform) :
			Actor{ tranform }
		{
		}

		Enemy(float speed, const nu::Tranform& tranform, const nu::Model& model) :
			m_speed{ speed },
			Actor{ tranform, model }
		{
		}

		void Update(float dt);
		void Draw(const class nu::Renderer& renderer) const;



	private:
		int m_ammo = 0;
		float m_speed = 800.0f;
	};
}

