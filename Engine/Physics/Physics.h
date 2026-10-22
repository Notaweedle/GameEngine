#pragma once
#include "Math/Vector2.h"
#include <box2d/box2d.h>

namespace nu
{

	class Physics
	{
	public:
		Physics() = default;

		~Physics() { Shutdown(); }

		static constexpr float PixelsPerUnit = 48.0f;
		
		void Initialize(const Vector2& gravity = Vector2{ 0.0f, 9.81f })
		{
			

			b2WorldDef worldDef = b2DefaultWorldDef();
			worldDef.gravity = b2Vec2{ 0.0f, 0.0f };	
			m_worldId = b2CreateWorld(&worldDef);
		}

		
		void Shutdown()
		{
			if (b2World_IsValid(m_worldId))
			{
				b2DestroyWorld(m_worldId);
				m_worldId = b2_nullWorldId;
			}
		}

		
		void Step(float dt, int subStepCount = 4)
		{
			if (b2World_IsValid(m_worldId))
			{
				b2World_Step(m_worldId, dt, subStepCount);
			}
		}

		

		static Vector2 PixelToWorld(const Vector2& v) { return v / PixelsPerUnit; }
		static Vector2 WorldToPixel(const Vector2& v) { return v * PixelsPerUnit; }

		
		static b2Vec2  ToB2(const Vector2& v)     { return b2Vec2{ v.x, v.y }; }
		static Vector2 ToVector2(const b2Vec2& v) { return Vector2{ v.x, v.y }; }

	public:
		b2WorldId m_worldId{ b2_nullWorldId };
	};
}
