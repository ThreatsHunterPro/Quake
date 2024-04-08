#include "FVector2.h"
#include "../FMath.h"

FVector2 FVector2::ZeroVector = FVector2(0, 0);
FVector2 FVector2::UnitVector = FVector2(1, 1);
FVector2 FVector2::Unit45Deg = FVector2(FMath::Sqrt(0.5f), FMath::Sqrt(0.5f));

FVector2::FVector2() : FVector2(0) {}

FVector2::FVector2(float _value)
{
	X = Y = _value;
}

FVector2::FVector2(float _x, float _y)
{
	X = _x;
	Y = _y;
}

FVector2::FVector2(const FVector2& _other)
{
	X = _other.X;
	Y = _other.Y;
}

float FVector2::CrossProduct(const FVector2& _a, const FVector2& _b) //STATIC
{
	return _a ^ _b;
}

float FVector2::Distance(const FVector2& _a, const FVector2& _b)
{
	return FMath::Sqrt(FVector2::DistSquared(_a, _b));
}

float FVector2::DistSquared(const FVector2& _a, const FVector2& _b)
{
	return FMath::Square(_a.X - _b.X) + FMath::Square(_a.Y - _b.Y);
}

float FVector2::DotProduct(const FVector2& _a, const FVector2& _b)
{
	return _a | _b;
}

bool FVector2::Normalize(float _tolerance)
{
	const float _squareSum = SquaredLength();
	if (_squareSum > _tolerance)
	{
		const float _scale = FMath::InvSqrt(_squareSum);
		X *= _scale;
		Y *= _scale;
		return true;
	}
	X = 0.0f;
	Y = 0.0f;
	return false;
}

FVector2 FVector2::GetSafeNormal(float _tolerance) const
{
	const float _squareSum = SquaredLength();
	if (_squareSum > _tolerance)
	{
		const float _scale = FMath::InvSqrt(_squareSum);
		return FVector2(X * _scale, Y * _scale);
	}
	return FVector2::ZeroVector;
}

FString FVector2::ToString() const
{
	return FString::Format("X={} Y={}", X, Y);
}

float FVector2::Length() const
{
	return FMath::Sqrt(X * X + Y * Y);
}

float FVector2::SquaredLength() const
{
	return X * X + Y * Y;
}

FVector2 FVector2::operator+(const FVector2& _other) const
{
	return FVector2(X + _other.X, Y + _other.Y);
}

FVector2 FVector2::operator+(float _a) const
{
	return FVector2(X +_a, Y+_a);
}

FVector2 FVector2::operator-(const FVector2& _other) const
{
	return FVector2(X - _other.X, Y - _other.Y);
}

FVector2 FVector2::operator-(float _a) const
{
	return FVector2(X - _a, Y - _a);
}

FVector2 FVector2::operator*(const FVector2& _other) const
{
	return FVector2(X * _other.X, Y * _other.Y);
}

FVector2 FVector2::operator*(float _scale) const
{
	return FVector2(X * _scale, Y * _scale);
}

FVector2 FVector2::operator/(const FVector2& _other) const
{
	return FVector2(X / _other.X, Y / _other.Y);
}

FVector2 FVector2::operator/(float _scale) const
{
	const float _RScale = 1.f / _scale;
	return FVector2(X * _RScale, Y * _RScale);
}

float FVector2::operator|(const FVector2& _other) const
{
	return X * _other.X + Y * _other.Y;
}

float FVector2::operator^(const FVector2& _other) const
{
	return X * _other.Y - Y * _other.X;
}

bool FVector2::operator==(const FVector2& _other) const
{
	return X == _other.X && Y == _other.Y;
}

bool FVector2::operator!=(const FVector2& _other) const
{
	return X != _other.X || Y != _other.Y;
}

FVector2 FVector2::operator-() const
{
	return FVector2(-X,-Y);
}

FVector2 FVector2::operator+=(const FVector2& _other)
{
	X += _other.X;
	Y += _other.Y;
	return *this;
}

FVector2 FVector2::operator+=(const float& _a)
{
	X += _a;
	Y += _a;
	return *this;
}

FVector2 FVector2::operator-=(const FVector2& _other)
{
	X -= _other.X;
	Y -= _other.Y;
	return *this;
}

FVector2 FVector2::operator-=(const float& _a)
{
	X -= _a;
	Y -= _a;
	return *this;
}

FVector2 FVector2::operator*=(const FVector2& _other)
{
	X *= _other.X;
	Y *= _other.Y;
	return *this;
}

FVector2 FVector2::operator*=(float _scale)
{
	X *= _scale;
	Y *= _scale;
	return *this;
}

FVector2 FVector2::operator/=(const FVector2& _other)
{
	X /= _other.X;
	Y /= _other.Y;
	return *this;
}

FVector2 FVector2::operator/=(float _a)
{
	const float _RV = 1.f / _a;
	X *= _RV; Y *= _RV;
	return *this;
}

float& FVector2::operator[](int _index)
{
	if (_index >= 0 && _index < 2)
		throw(exception("[FVector2] => Index out of range; Index: " + _index));
	return ((_index == 0) ? X : Y);
}

float FVector2::operator[](int _index) const
{
	if (_index >= 0 && _index < 2)
		throw(exception("[FVector2] => Index out of range; Index: " + _index));
	return ((_index == 0) ? X : Y);
}
