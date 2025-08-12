#include "vector2.h"

Vector2::Vector2(float x, float y) : m_x(x), m_y(y) 
{

}

Vector2::Vector2(const Vector2& other) : m_x(other.m_x), m_y(other.m_y)
{

}

Vector2& Vector2::operator=(const Vector2& other)
{
	if (this != &other)
	{
		this->m_x = other.m_x, this->m_y = other.m_y;
	}
	return *this;
}

Vector2& Vector2::operator=(Vector2&& other) noexcept
{
	if (this != &other)
	{
		this->m_x = std::move(other.m_x), this->m_y = std::move(other.m_y);
	}
	return *this;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(this->m_x + other.m_x, this->m_y + other.m_y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(this->m_x - other.m_x, this->m_y - other.m_y);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-this->m_x, -this->m_y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(this->m_x * scalar, this->m_y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
	if (!scalar) return Vector2(this->m_x, this->m_y);
	return Vector2(this->m_x / scalar, this->m_y / scalar);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->m_x += other.m_x, this->m_y += other.m_y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	this->m_x -= other.m_x, this->m_y -= other.m_y;
	return *this;
}

Vector2& Vector2::operator*=(float scalar)
{
	this->m_x *= scalar, this->m_y *= scalar;
	return *this;
}

Vector2& Vector2::operator/=(float scalar)
{
	if (!scalar) return *this;
	this->m_x /= scalar, this->m_y /= scalar;
	return *this;
}

bool Vector2::operator==(const Vector2& other) const
{
	return this->m_x == other.m_x && this->m_y == other.m_y;
}

bool Vector2::operator!=(const Vector2& other) const
{
	return !(*this == other);
}

float Vector2::length() const
{
	return sqrt(this->m_x * this->m_x + this->m_y * this->m_y);
}

Vector2 Vector2::normalize() const
{
	float len = this->length();

	if (len == 0) return Vector2(0, 0);

	return Vector2(this->m_x / len, this->m_y / len);
}