#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "Random.h"
#include <cmath>

namespace nu
{
	ParticleSystem::ParticleSystem(int poolSize)
	{
		m_particles.resize(poolSize);
	}

	void ParticleSystem::Emit(const ParticleDesc& desc)
	{
		for (int i = 0; i < desc.count; i++)
		{
			
			Particle* particles = nullptr;
			for (auto& particle : m_particles)
			{
				if (!particle.isActive)
				{
					particles = &particle;
					break;
				}
			}
			if (particles == nullptr) break; 

			
			float angle = desc.angle + RandomFloat(-desc.angleVariance, desc.angleVariance);
			float speed = desc.speed + RandomFloat(-desc.speedVariance, desc.speedVariance);

			particles->position = desc.position;
			particles->velocity = Vector2{ std::cos(angle), std::sin(angle) } * speed;
			particles->lifetime = desc.lifetime + RandomFloat(-desc.lifetimeVariance, desc.lifetimeVariance);
			if (particles->lifetime < 0.1f) particles->lifetime = 0.1f;
			particles->maxLifetime = particles->lifetime;
			particles->color = desc.color;
			particles->isActive = true;
		}
	}

	void ParticleSystem::Update(float dt)
	{
		for (auto& particle : m_particles)
		{
			if (!particle.isActive) continue;

			particle.lifetime -= dt;
			if (particle.lifetime <= 0.0f)
			{
				particle.isActive = false;
				continue;
			}

			particle.position += particle.velocity * dt;

			float t = particle.lifetime / particle.maxLifetime;
			particle.color.a = t;
		}
	}

	void ParticleSystem::Draw(const Renderer& renderer) const
	{
		for (auto& particles : m_particles)
		{
			if (!particles.isActive) continue;

			renderer.SetColor(particles.color.r, particles.color.g, particles.color.b, particles.color.a);
			renderer.DrawFillRect(particles.position.x - 1.0f, particles.position.y - 1.0f, 2.0f, 2.0f);
		}
	}
}
