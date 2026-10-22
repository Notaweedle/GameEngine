#pragma once 
#include "Framework/Actor.h"
#include "Renderer/Model.h"
namespace nu {



	class Enemy : public nu::Actor {
	public:
		Enemy() = default;
		Enemy(float speed, const nu::Transform& transform) :
			Actor{ transform }, m_speed{ speed }
		{
		}

		Enemy(float speed, const nu::Transform& transform, const nu::Model& model) :
			Actor{ transform, model }, m_speed{ speed }
		{
		}

		CLASS_PROTOTYPE(Enemy)

		void Update(float dt) override;
		void Draw(const class nu::Renderer& renderer) const override;
		void Read(const nu::json::value_t& value);

		
		void OnKilled() override;

		

		


	private:
		
		int m_ammo = 0;
		int m_health =  1;
		int m_points =  100;
		float m_speed = 400.0f;
	};

}

