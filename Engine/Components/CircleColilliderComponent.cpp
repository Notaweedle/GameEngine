#include "pch.h"
#include "CircleColilliderComponent.h"
#include "Factory.h"
#include "Actor.h"

namespace nu
{
	FACTORY_REGISTER(CircleColilliderComponent)

	bool CircleColilliderComponent::CheckCollision(const ColilliderComponent& other)
	{
		//TODO Change this to make it all Colillider Components
		const CircleColilliderComponent* cir = dynamic_cast<const CircleColilliderComponent*>(&other);
		if (cir == nullptr) return false;

		float distance = GetOwner()->getTransform().position.Distance(other.GetOwner()->getTransform().position);
		return distance <= m_radius + cir->GetRadius();
	}

	void CircleColilliderComponent::Read(const json::value_t& value)
	{
		JSON_READ_NAME(value, "radius", m_radius);
	}
}
