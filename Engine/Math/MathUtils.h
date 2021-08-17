#pragma once

namespace nc {
	const float Pi = 3.141592653589793238462643f;
	const float TwoPi = 6.28318531f;
	const float HalfPi = 1.57079633f;
	const float QuarterPi = 0.785398163f;

	inline float RadToDeg(float radians) {
		return radians * 180.0f / Pi; 
	}

	inline float DegToRad(float degrees) {
		return degrees * Pi / 180.0f;
	}

	template<typename T>
	T Clamp(T value, T min, T max) {
		if (value < min) return min;
		if (value > max) return max;

		return value;
	}

	template<typename T>
	T Wrap(T value, T min, T max) {
		if (value < min) return max;
		if (value > max) return min;

		return value;
	}

	template<typename T>
	T Lerp(T a, T b, float t) {
		t = Clamp(t, 0.0f, 1.0f);

		return a + ((b - a) * t);
	}
}