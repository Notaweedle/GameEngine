#pragma once
#include "Components/ColliderComponet.h"

namespace nu
{
	class CircleColilliderComponent : public ColilliderComponent
	{
	public:
		CLASS_PROTOTYPE(CircleColilliderComponent)

		bool CheckCollision(const ColilliderComponent& other) override;
		void Read(const json::value_t& value) override;

		float GetRadius() const override { return m_radius; }

	protected:
		float m_radius = 0.0f;
	};
}
