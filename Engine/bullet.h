#pragma once
#include "Actor.h"
#include "Model.h"

namespace nu  {
	class bullet : public nu::Actor {
	public:
		bullet() = default;

		bullet(float speed, const nu::Tranform& tranform) :
			Actor{ tranform },
			m_speed{ speed }
		{
		}

		bullet(float speed, const nu::Tranform& tranform, const nu::Model& model) :
			Actor{ tranform, model },
			m_speed{ speed }
		{
		}

		void Update(float dt) override;
		void Draw(const class nu::Renderer& renderer) const override;

		void setLifespan(float lifespan) { m_lifespan = lifespan; }

	private:
		float m_speed = 2000.0f;
		float m_lifespan = 1.5f;
	};
}
