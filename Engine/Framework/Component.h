#pragma once
#include "object.h"
#include "Serialization/json.h"
namespace nu {
	class Actor;

	class Component : public Object
	{
	public :
		Component() = default;
		virtual ~Component() = default;

		virtual void Start() {}
		virtual void onDestroy() {}

		virtual void Update(float dt) {}
		virtual void Read(const json::value_t& value) {}
		Actor* GetOwner() const { return m_owner; }
		void SetOwner(Actor* owner) { m_owner = owner; }
		

	protected:
		Actor* m_owner = nullptr;
	};
}
