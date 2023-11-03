#pragma once
#include <iostream>
using namespace std;
class Vector2D
{
public:
	Vector2D();
	Vector2D(float x, float y);

	Vector2D& operator + (const Vector2D& rhs) const;

	Vector2D& operator - (const Vector2D& rhs) const;

	Vector2D& operator * (const Vector2D& rhs) const ;

	Vector2D& operator / (const Vector2D& rhs) const ;




	Vector2D operator += (const Vector2D& rhs) ;

	Vector2D operator -= (const Vector2D& rhs) ;

	Vector2D operator *= (const Vector2D& rhs) ;

	Vector2D operator /= (const Vector2D& rhs) ;

	Vector2D zero();

	friend ostream& operator<<(ostream& stream, const Vector2D& vec);

	float x;
	float y;


};