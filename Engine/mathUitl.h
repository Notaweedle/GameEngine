#pragma once
namespace nu::math {
	constexpr float pi = 3.14159265358979f;
	constexpr float HalfPi = pi / 2;
	constexpr float TwoPi = pi * 2;

	constexpr float RadToDeg = 180.0f / pi;
	constexpr float DegToRad = pi / 180.0f;

	inline float randomf(float min, float max) {
		return min + (max - min) * (rand() / static_cast<float>(RAND_MAX));
	}

	template<typename T>
	T Max(T a, T b) {
		
		return (a > b) ? a : b;
	}

	template<typename T>
	T Min(T a, T b) {
		
		return (a < b) ? a : b;
	}

	template<typename T>
	T Wrap(T min, T max, T value) {
		if (value > max) value = min;
		if (value < min) value = max;

		return value;

	}

	template<typename T>
	T Clamp(T min, T max, T value) {
		if (value > max) value = max;
		if (value < min) value = min;
		return value;
	}
}