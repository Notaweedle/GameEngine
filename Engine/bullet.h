#pragma once
#include "Actor.h"
#include "Model.h"

namespace nu  {
	class Bullet : public nu::Actor {
	public:
		Bullet() = default;

		Bullet(float speed, const nu::Transform& transform) :
			Actor{ transform },
			m_speed{ speed }
		{
		}

		Bullet(float speed, const nu::Transform& transform, const nu::Model& model) :
			Actor{ transform, model },
			m_speed{ speed }
		{
		}

		CLASS_PROTOTYPE(Bullet)

		void Update(float dt) override;
		void Draw(const class nu::Renderer& renderer) const override;

		void setLifespan(float lifespan) { m_lifespan = lifespan; }

		void Read(const nu::json::value_t& value) override;

	private:
		float m_speed = 2000.0f;
		float m_bulletSpeed = 1400.0f;
		float m_lifespan = 1.5f;
	};
}
