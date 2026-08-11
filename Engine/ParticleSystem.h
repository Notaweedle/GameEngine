#pragma once
#include "Vector2.h"
#include "Color.h"
#include "mathUitl.h"
#include "Resource.h"   // res_t
#include <vector>

namespace nu
{
	class Renderer;
	class Texture;

	struct Particle
	{
		Vector2 position = {0.f,0.f};
		Vector2 velocity = {0.f,0.f};
		Color color {1.f,1.f,1.f,1.f};
		float lifetime = 0.0f;  
		float maxLifetime = 1.0f;
		bool isActive = false;
	};

	struct ParticleDesc
	{
		Vector2 position = {0.f,0.f};
		Vector2 velocity = {0.f,0.f};         
		double speed = 100.0f;
		float speedVariance = 50.0f;
		float angle = 0.0f;      
		float angleVariance = nu::math::pi; 
		float lifetime = 1.0f;
		float lifetimeVariance = 0.5f;
		Color color{ 1.0f, 1.0f, 1.0f, 1.0f };
		int count = 10;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;
		explicit ParticleSystem(int poolSize);

		void Emit(const ParticleDesc& desc);
		void Update(float dt);
		void Draw(const Renderer& renderer) const;

		void SetTexture(res_t<Texture> texture) { m_texture = texture; }

	private:
		std::vector<Particle> m_particles;
		res_t<Texture> m_texture;   // sprite used to draw each particle
	};
}
