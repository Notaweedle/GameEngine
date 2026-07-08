#pragma once
#include <cstdlib>
namespace nu {

	inline int RandomInt() {
		return rand();
	}
	/// <summary>
	/// Get random int value (0, max)
	/// </summary>
	/// <param name="max"> Exclusive Max </param>
	/// <returns>returns random number that is between 0 though max.</returns>
	inline int RandomInt(int max) {
		return rand() % max;
	}

	/// <summary>
	/// Get's a random int value (min, max)
	/// </summary>
	/// <param name="min">Inclusive</param>
	/// <param name="max">Inclusive</param>
	/// <returns>Returns a int value between min and max </returns>
	inline int RandomInt(int min, int max) {
		return min + RandomInt(max - min) + 1;
	}
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>

	
	inline float RandomFloat() {
		// rand() = 0 <- RAND_MAX
		return rand() / RAND_MAX;
	}
	inline float RandomFloat(float max) {
		// 0 <-> 1 * max
		return RandomFloat() * max;
	}
	inline float RandomFloat(float min, float max) {
		//min + (0 <-> 1) * (max - min)
		return min + RandomFloat() * (max - min);
	}
}
