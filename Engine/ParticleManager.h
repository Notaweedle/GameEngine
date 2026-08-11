#pragma once
#include "ParticleSystem.h"


namespace nu {

	inline ParticleDesc enmy_expl() {
		
		ParticleDesc pd;
		pd.position = { 0.f,0.f };
		pd.speed = 150.0f;
		pd.speedVariance = 80.0f;
		pd.lifetime = 0.8f;
		pd.lifetimeVariance = 0.3f;
		pd.color = Color{ 1.0f, 0.5f, 0.0f, 1.0f };
		pd.count = 20;
		return pd;
	}
	inline ParticleDesc player_expl() {
		
		ParticleDesc pd;
		pd.position = { 0.f,0.f };
		pd.speed = 200.0f;
		pd.speedVariance = 100.0f;
		pd.lifetime = 1.0f;
		pd.lifetimeVariance = 0.4f;
		pd.color = Color{ 1.0f, 0.2f, 0.2f, 1.0f };
		pd.count = 30;
		return pd;
	}


}