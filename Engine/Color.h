#pragma once
#include <cassert>
namespace nu
{
	class Color
	{
	public:
		float r, g, b, a;


		Color() = default;
		Color(float r, float g, float b, float a = 1.0f) : r{ r }, g{ g }, b{ b }, a{ a } {}
		explicit Color(float v) : r{ v }, g{ v }, b{ v }, a{ 1.0f } {}



		float  operator [] (unsigned int i) const { assert(i < 4); return (&r)[i]; }
		float& operator [] (unsigned int i) { assert(i < 4); return (&r)[i]; }

		bool operator == (const Color& c) const { return this->r == c.r && this->g == c.g && this->b == c.b && this->a == c.a; }
		bool operator != (const Color& c) const { return !(*this == c); }

		Color operator + (const Color& c) const { return Color{ this->r + c.r, this->g + c.g, this->b + c.b, this->a + c.a }; }
		Color operator - (const Color& c) const { return Color{ this->r - c.r, this->g - c.g, this->b - c.b, this->a - c.a }; }
		Color operator * (const Color& c) const { return Color{ this->r * c.r, this->g * c.g, this->b * c.b, this->a * c.a }; }
		Color operator / (const Color& c) const { return Color{ this->r / c.r, this->g / c.g, this->b / c.b, this->a / c.a }; }

		Color operator + (float v) const { return Color{ this->r + v, this->g + v, this->b + v, this->a + v }; }
		Color operator - (float v) const { return Color{ this->r - v, this->g - v, this->b - v, this->a - v }; }
		Color operator * (float v) const { return Color{ this->r * v, this->g * v, this->b * v, this->a * v }; }
		Color operator / (float v) const { return Color{ this->r / v, this->g / v, this->b / v, this->a / v }; }

		Color& operator += (const Color& c) { this->r += c.r; this->g += c.g; this->b += c.b; this->a += c.a; return *this; }
		Color& operator -= (const Color& c) { this->r -= c.r; this->g -= c.g; this->b -= c.b; this->a -= c.a; return *this; }
		Color& operator *= (const Color& c) { this->r *= c.r; this->g *= c.g; this->b *= c.b; this->a *= c.a; return *this; }
		Color& operator /= (const Color& c) { this->r /= c.r; this->g /= c.g; this->b /= c.b; this->a /= c.a; return *this; }

		Color& operator += (float v) { this->r += v; this->g += v; this->b += v; this->a += v; return *this; }
		Color& operator -= (float v) { this->r -= v; this->g -= v; this->b -= v; this->a -= v; return *this; }
		Color& operator *= (float v) { this->r *= v; this->g *= v; this->b *= v; this->a *= v; return *this; }
		Color& operator /= (float v) { this->r /= v; this->g /= v; this->b /= v; this->a /= v; return *this; }
	};
}
