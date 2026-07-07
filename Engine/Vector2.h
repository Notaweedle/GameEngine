#pragma once
#include <cmath>
namespace nu 
{
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2() = default;
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(float v) : x{ v }, y{ v } {}



		Vector2 operator + (const Vector2& v) { return Vector2{ this->x + v.x,this->y + v.y }; }
		Vector2 operator - (const Vector2& v) { return Vector2{ this->x - v.x,this->y - v.y }; }
		Vector2 operator * (const Vector2& v) { return Vector2{ this->x * v.x,this->y * v.y }; }
		Vector2 operator / (const Vector2& v) { return Vector2{ this->x / v.x,this->y / v.y }; }

		Vector2 operator + (float v) { return Vector2{ this->x + v,this->y + v }; }
		Vector2 operator - (float v) { return Vector2{ this->x - v,this->y - v }; }
		Vector2 operator * (float v) { return Vector2{ this->x * v,this->y * v }; }
		Vector2 operator / (float v) { return Vector2{ this->x / v,this->y / v }; }

		Vector2 operator += (const Vector2& v) { this->x += v.x, this->y += v.y; return *this; }
		Vector2 operator -= (const Vector2& v) { this->x -= v.x, this->y -= v.y; return *this; }
		Vector2 operator *= (const Vector2& v) { this->x *= v.x, this->y *= v.y; return *this; }
		Vector2 operator /= (const Vector2& v) { this->x /= v.x, this->y /= v.y; return *this; }


		Vector2 operator += ( float v) { this->x += v, this->y += v; return *this; }
		Vector2 operator -= ( float v) { this->x -= v, this->y -= v; return *this; }
		Vector2 operator *= ( float v) { this->x *= v, this->y *= v; return *this; }
		Vector2 operator /= ( float v) { this->x /= v, this->y /= v; return *this; }


		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return sqrt(LengthSqr()); }
	};
}