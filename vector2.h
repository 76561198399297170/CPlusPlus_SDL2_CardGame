#ifndef _VECTOR2_H_
#define _VECTOR2_H_

#include <cmath>
#include <algorithm>


class Vector2
{
public:
	Vector2() = default;
	Vector2(float x, float y);
	Vector2(const Vector2& other);
	~Vector2() = default;

	Vector2& operator=(const Vector2& other);
	Vector2& operator=(Vector2&& other) noexcept;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator-() const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;
	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);
	bool operator==(const Vector2& other) const;
	bool operator!=(const Vector2& other) const;

	float length() const;

	Vector2 normalize() const;

public:
	float m_x;
	float m_y;

};

#endif
