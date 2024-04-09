#include "FVector4.h"
#include "TVector.h"
FVector4 FVector4::ZeroVector = FVector4();
FVector4 FVector4::One = FVector4(1);


FVector4::FVector4() : FVector4(0)
{
}

FVector4::FVector4(float _a)
{
	X = _a;
	Y = _a;
	Z = _a;
	W = _a;
}

FVector4::FVector4(const FVector4& _other)
{
	X = _other.X;
	Y = _other.Y;
	Z = _other.Z;
	W = _other.W;
}

FVector4::FVector4(const FVector& _other, float _w)
{
	X = _other.X;
	Y = _other.Y;
	Z = _other.Z;
	W = _w;
}

FVector4::FVector4(FVector2 _XY, FVector2 _ZW)
{
	X = _XY.X;
	Y = _XY.Y;
	Z = _ZW.X;
	W = _ZW.Y;
}

FVector4::FVector4(float _x, float _y, float _z, float _w)
{
	W = _w;
	X = _x;
	Y = _y;
	Z = _z;

}

FString FVector4::ToString() const
{
	return FString::Format(" W={} X={} Y={} Z={}",W, X, Y,Z);
}

bool FVector4::Equals(const FVector4& _other, float _tolerance) const
{
	return FMath::Abs(X - _other.X) <= _tolerance && FMath::Abs(Y - _other.Y) <= _tolerance && FMath::Abs(Z - _other.Z) <= _tolerance && FMath::Abs(W - _other.W) <= _tolerance;
}

FRotator FVector4::ToOrientationRotator() const
{
	FRotator _r;
	_r.Yaw = FMath::RadiansToDegrees(FMath::ATan2(Y, X));
	_r.Pitch = FMath::RadiansToDegrees(FMath::ATan2(Z, FMath::Sqrt(X * X + Y * Y)));
	_r.Roll = 0;
	return _r;
}

FRotator FVector4::Rotation() const
{
	return ToOrientationRotator();
}

float FVector4::Size3() const
{
	return FMath::Sqrt(X * X + Y * Y + Z * Z);
}

FQuat FVector4::ToOrientationQuat() const
{
	const float _yawRad = FMath::ATan2(Y, X);
	const float _pitchRad = FMath::ATan2(Z, FMath::Sqrt(X * X + Y * Y));

	const float DIVIDE_BY_2 = 0.5;
	float _SP, _SY;
	float _CP, _CY;

	FMath::SinCos(&_SP, &_CP, _pitchRad * DIVIDE_BY_2);
	FMath::SinCos(&_SY, &_CY, _yawRad * DIVIDE_BY_2);

	FQuat _rotationQuat;
	_rotationQuat.X = _SP * _SY;
	_rotationQuat.Y = -_SP * _CY;
	_rotationQuat.Z = _CP * _SY;
	_rotationQuat.W = _CP * _CY;
	return _rotationQuat;
}

FVector4 FVector4::GetUnsafeNormal3() const
{
	const float _scale = FMath::InvSqrt(X * X + Y * Y + Z * Z);
	return FVector4(X * _scale, Y * _scale, Z * _scale, 0.0f);
}

float FVector4::SizeSquared3() const
{
	return X * X + Y * Y + Z * Z;
}

float FVector4::Size() const
{
	return FMath::Sqrt(X * X + Y * Y + Z * Z + W * W);
}

float FVector4::SizeSquared() const
{
	return X * X + Y * Y + Z * Z + W * W;
}

float FVector4::Dot3(const FVector4& _vec1, const FVector4& _vec2)
{
	return _vec1.X * _vec1.X + _vec1.Y * _vec1.Y + _vec1.Z * _vec1.Z;
}
float FVector4::Dot3(const FVector4& _vec1, const FVector& _vec2)
{
	return _vec1.X * _vec1.X + _vec1.Y * _vec1.Y + _vec1.Z * _vec1.Z;
}
float FVector4::Dot4(const FVector4& _vec1, const FVector4& _vec2)
{
	return _vec1.X * _vec1.X + _vec1.Y * _vec1.Y + _vec1.Z * _vec1.Z + _vec1.W * _vec2.W;
}

FVector4 FVector4::operator-(const FVector4& _v)
{
	return FVector4(X - _v.X, Y - _v.Y, Z - _v.Z, W - _v.W);
}

const FVector4 FVector4::operator-()
{
	return FVector4(-X, -Y, -Z, -W);
}

const bool FVector4::operator!=(const FVector4& _v)
{
	return ((X != _v.X) || (Y != _v.Y) || (Z != _v.Z) || (W != _v.W));
}
const bool FVector4::operator==(const FVector4& _v)
{
	return ((X == _v.X) && (Y == _v.Y) && (Z == _v.Z) && (W == _v.W));
}

const FVector4 FVector4::operator*(const FVector4& _v)
{
	return FVector4(X * _v.X, Y * _v.Y, Z * _v.Z, W * _v.W);
}

const FVector4 FVector4::operator*(float _scale)
{
	return FVector4(X * _scale, Y * _scale, Z * _scale, W * _scale);
}

FVector4 FVector4::operator*=(float _s)
{
	X *= _s; Y *= _s; Z *= _s; W *= _s;
	return *this;
}

FVector4 FVector4::operator*=(const FVector4& _v)
{
	X *= _v.X; Y *= _v.Y; Z *= _v.Z; W *= _v.W;
	return *this;
}

const FVector4 FVector4::operator/(float _scale)
{
	const float _rScale = 1.0f / _scale;
	return FVector4(X * _rScale, Y * _rScale, Z * _rScale, W * _rScale);
}

const FVector4 FVector4::operator/(const FVector4& _v)
{
	return FVector4(X / _v.X, Y / _v.Y, Z / _v.Z, W / _v.W);
}

FVector4 FVector4::operator/=(const FVector4& _v)
{
	X /= _v.X; Y /= _v.Y; Z /= _v.Z; W /= _v.W;
	return *this;
}

const FVector4 FVector4::operator^(const FVector4& _v)
{
	return FVector4(
		Y * _v.Z - Z * _v.Y,
		Z * _v.X - X * _v.Z,
		X * _v.Y - Y * _v.X,
		0.0f);
}

const FVector4 FVector4::operator+(const FVector4& _v)
{
	return FVector4(X + _v.X, Y + _v.Y, Z + _v.Z, W + _v.W);
}

FVector4 FVector4::operator+=(const FVector4& _v)
{
	X += _v.X; Y += _v.Y; Z += _v.Z; W += _v.W;
	return *this;
}

FVector4 FVector4::operator-=(const FVector4& _v)
{
	X -= _v.X; Y -= _v.Y; Z -= _v.Z; W -= _v.W;
	return *this;
}
