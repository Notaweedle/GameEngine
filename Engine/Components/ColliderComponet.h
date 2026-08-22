#pragma once
#include "Framework/Component.h"

namespace nu
{
	
	class ColilliderComponent : public Component
	{
	public:
		virtual bool CheckCollision(const ColilliderComponent& other) = 0;
		virtual float GetRadius() const { return 0.0f; }
	};
}
