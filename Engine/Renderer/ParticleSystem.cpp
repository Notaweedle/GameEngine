#include "pch.h"
#include "ParticleSystem.h"
#include "Renderer.h"
#include "Texture.h"
#include "Core/Random.h" n
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
			float speed = static_cast<float>(desc.speed) + RandomFloat(-desc.speedVariance, desc.speedVariance);

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
		for (auto& p : m_particles)
		{
			if (!p.isActive) continue;

			if (m_texture)
			{
				// Draw each particle as a sprite, shrinking as its life runs out.
				float t = (p.maxLifetime > 0.0f) ? (p.lifetime / p.maxLifetime) : 1.0f; // 1 -> 0
				float scale = 0.6f * t + 0.1f;
				renderer.DrawTexture(m_texture.get(), p.position.x, p.position.y, 0.0f, scale, p.color);
			}
			else
			{
				renderer.SetColor(p.color.r, p.color.g, p.color.b, p.color.a);
				renderer.DrawFillRect(p.position.x - 1.0f, p.position.y - 1.0f, 2.0f, 2.0f);
			}
		}
	}
}
