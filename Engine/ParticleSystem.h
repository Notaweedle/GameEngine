#pragma once
#include "Vector2.h"
#include "Color.h"
#include <vector>

namespace nu
{
	class Renderer;

	struct Particle
	{
		Vector2 position;
		Vector2 velocity;
		Color color;
		float lifetime = 0.0f;  // time remaining
		float maxLifetime = 1.0f;
		bool isActive = false;
	};

	struct ParticleDesc
	{
		Vector2 position;
		Vector2 velocity;         // base direction
		float speed = 100.0f;
		float speedVariance = 50.0f;
		float angle = 0.0f;       // spread centre (radians)
		float angleVariance = 3.14159f; // spread range
		float lifetime = 1.0f;
		float lifetimeVariance = 0.5f;
		Color color{ 1.0f, 1.0f, 1.0f, 1.0f };
		int count = 10;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;
		ParticleSystem(int poolSize);

		void Emit(const ParticleDesc& desc);
		void Update(float dt);
		void Draw(const Renderer& renderer) const;

	private:
		std::vector<Particle> m_particles;
	};
}
