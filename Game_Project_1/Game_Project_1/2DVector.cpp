#include "2DVector.h"

Vector2D::Vector2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float tempX, float tempY)
{
	this->x = tempX;
	this->y = tempY;


}

Vector2D& Vector2D::operator+(const Vector2D& rhs) const
{
	return *new Vector2D(this->x + rhs.x, this->y + rhs.y);
}

Vector2D& Vector2D::operator-(const Vector2D& rhs) const
{
	return *new Vector2D(this->x - rhs.x, this->y - rhs.y);
}

Vector2D& Vector2D::operator*(const Vector2D& rhs) const
{
	return *new Vector2D(this->x * rhs.x, this->y * rhs.y);
}

Vector2D& Vector2D::operator/(const Vector2D& rhs) const
{
	return *new Vector2D(this->x / rhs.x, this->y / rhs.y);
}

Vector2D Vector2D::operator += (const Vector2D& rhs)
{
	this->x += rhs.x;
	return *this;
}

Vector2D Vector2D::operator -= (const Vector2D& rhs)
{
	this->x -= rhs.x;
	return *this;
}

Vector2D Vector2D::operator *= (const Vector2D& rhs)
{
	this->x *= rhs.x;
	return *this;
}

Vector2D Vector2D::operator /= (const Vector2D& rhs)
{
	this->x /= rhs.x;
	return *this;
}

Vector2D Vector2D::zero()
{
	this->x = 0;
	this->y = 0;
	return *this;
}

ostream& operator<<(ostream& stream, const Vector2D& vec)
{
	stream << "( " << vec.x << ", " << vec.y << ")";
	return stream;
}