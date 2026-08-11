#pragma once
#include <cstdlib>
#include <random>
namespace nu {

	inline std::mt19937& Generator() {
		std::random_device random_device;
		static std::mt19937 generator(random_device());

		return generator;
	}

	inline void SeedRandom(unsigned int seed) {
		Generator().seed(seed);
	}

	inline int RandomInt() {
		static std::uniform_int_distribution<> dist;
		return dist(Generator());
	}
	/// <summary>
	/// Get random int value (0, max)
	/// </summary>
	/// <param name="max"> Exclusive Max </param>
	/// <returns>returns random number that is between 0 though max.</returns>
	inline int RandomInt(int max) {
		std::uniform_int_distribution<> dist(0,max-1);
		return dist(Generator());
	}

	/// <summary>
	/// Get's a random int value (min, max)
	/// </summary>
	/// <param name="min">Inclusive</param>
	/// <param name="max">Inclusive</param>
	/// <returns>Returns a int value between min and max </returns>
	inline int RandomInt(int min, int max) {
		if (min > max) std::swap(min, max);
		std::uniform_int_distribution<> dist(min, max);
		return dist(Generator());
	}
	

	
	inline float RandomFloat() {
		static std::uniform_real_distribution<> dist;
		return dist(Generator());
	}
	inline float RandomFloat(float max) {
		 std::uniform_real_distribution<> dist(0.0f,max);
		return dist(Generator());
	}
	inline float RandomFloat(float min, float max) {
		if (min > max) std::swap(min, max);
		static std::uniform_real_distribution<> dist(min, max);
		return dist(Generator());
	}
	inline float RandomBool() {
		std::bernoulli_distribution dist(0.5f);
		return dist(Generator());
	}


}
