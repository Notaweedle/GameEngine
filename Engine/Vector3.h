#pragma once
#include <cmath>
#include <cassert>
namespace nu
{
	class Vector3
	{
	public:
		float x, y, z;


		Vector3() = default;
		Vector3(float x, float y, float z) : x{ x }, y{ y }, z{z} {}
		explicit Vector3(float v) : x{ v }, y{ v }, z{v} {}



		float  operator [] (unsigned int i) const { assert(i < 2); return (&x)[i]; }
		float& operator [] (unsigned int i) { assert(i < 2); return (&x)[i]; }

		bool operator == (const Vector3& v) const { return (this->x == v.x && this->y == v.y); }
		bool operator != (const Vector3& v) const { return (this->x != v.x && this->y != v.y) && this -> z != v.z; }

		Vector3 operator + (const Vector3& v) const { return Vector3{ this->x + v.x, this->y + v.y, this->z + v.z }; }
		Vector3 operator - (const Vector3& v) const { return Vector3{ this->x - v.x, this->y - v.y, this->z - v.z }; }
		Vector3 operator * (const Vector3& v) const { return Vector3{ this->x * v.x, this->y * v.y, this->z * v.z }; }
		Vector3 operator / (const Vector3& v) const { return Vector3{ this->x / v.x, this->y / v.y, this->z / v.z }; }

		Vector3 operator + (float v) const { return Vector3{ this->x + v,this->y + v, this->z + v }; }
		Vector3 operator - (float v) const { return Vector3{ this->x - v,this->y - v, this->z - v }; }
		Vector3 operator * (float v) const { return Vector3{ this->x * v,this->y * v, this->z * v }; }
		Vector3 operator / (float v) const { return Vector3{ this->x / v,this->y / v, this->z / v }; }

		Vector3& operator += (const Vector3& v) { this->x += v.x; this->y += v.y; this->z += v.z; return *this; }
		Vector3& operator -= (const Vector3& v) { this->x -= v.x; this->y -= v.y; this->z -= v.z; return *this; }
		Vector3& operator *= (const Vector3& v) { this->x *= v.x; this->y *= v.y; this->z *= v.z; return *this; }
		Vector3& operator /= (const Vector3& v) { this->x /= v.x; this->y /= v.y; this->z /= v.z; return *this; }

		Vector3& operator += (float v) { this->x += v; this->y += v; return *this; }
		Vector3& operator -= (float v) { this->x -= v; this->y -= v; return *this; }
		Vector3& operator *= (float v) { this->x *= v; this->y *= v; return *this; }
		Vector3& operator /= (float v) { this->x /= v; this->y /= v; return *this; }


		float LengthSqr() const { return (x * x) + (y * y) +(z * z); }
		float Length() const { return sqrt(LengthSqr()); }
		Vector3 Normalize() const { return (*this) / Length(); }
		float Dot(const Vector3& v) { return  (this->x * v.x) + (this->y * v.y) +(this -> z * v.z); }
		


	};
}