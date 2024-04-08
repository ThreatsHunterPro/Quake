#include "Quat.h"
#include "FVector/TVector.h"

FQuat FQuat::Identity = FQuat(0, 0, 0,1);

FQuat::FQuat(const FRotator& _rotator)
{
	X = _rotator.Pitch;
	Y = _rotator.Yaw;
	Z = _rotator.Roll;
	W = 1;
}

FQuat::FQuat(FRotator _axis, float _angleRad)
{
	X = _axis.Pitch;
	Y = _axis.Yaw;
	Z = _axis.Roll;
	W = _angleRad;
}

FQuat::FQuat(float _x, float _y, float _z, float _w)
{
	X = _x;
	Y = _y;
	Z = _z;
	W = _w;
}

float FQuat::GetAngle()const 
{
	return 2.0 * FMath::ACos(W);
}

float FQuat::GetTwistAngle(FVector& _twistAxis) const
{
	float XYZ = _twistAxis.DotProduct(FVector(X, Y, Z));
	return FMath::UnwindRadians(2.0f * FMath::ATan2(XYZ, W));
}

float FQuat::Size() const
{
	return FMath::Sqrt(X * X + Y * Y + Z * Z + W * W);
}

float FQuat::SizeSquared() const
{
	return X * X + Y * Y + Z * Z + W * W;
}

FVector FQuat::GetAxisX()
{
	return RotateVector(FVector(1.f, 0.f, 0.f));
}

FVector FQuat::GetAxisY()
{
	return RotateVector(FVector(0.f,1.f, 0.f));
}

FVector FQuat::GetAxisZ()
{
	return RotateVector(FVector(0.f, 0.f, 1.f));
}

FVector FQuat::GetForwardVector()
{
	return GetAxisX();
}

FVector FQuat::GetRightVector()
{
	return GetAxisY();
}

FVector FQuat::GetUpVector()
{
	return GetAxisZ();
}

FQuat FQuat::GetNormalized(float _tolerance) const
{
	FQuat _result(*this);
	_result.Normalize(_tolerance);
	return _result;
}

FRotator FQuat::GetRotator() const
{
	return FRotator(X,Y,Z);
}

bool FQuat::Equals(const FQuat& _other, float _tolerance)
{
	return (FMath::Abs(X - _other.X) <= _tolerance && FMath::Abs(Y - _other.Y) <= _tolerance && FMath::Abs(Z - _other.Z) <= _tolerance && FMath::Abs(W - _other.W) <= _tolerance)
		|| (FMath::Abs(X + _other.X) <= _tolerance && FMath::Abs(Y + _other.Y) <= _tolerance && FMath::Abs(Z + _other.Z) <= _tolerance && FMath::Abs(W + _other.W) <= _tolerance);
}

bool FQuat::IsIdentity(float _tolerence)
{
	return Equals(FQuat::Identity, _tolerence);
}

bool FQuat::IsNormalized()
{
	return (FMath::Abs(1.f - SizeSquared()) < 0.01f);
}

float FQuat::AngularDistance(const FQuat& _quat) const
{
	float InnerProd = X * _quat.X + Y * _quat.Y + Z * _quat.Z + W * _quat.W;
	return FMath::ACos((2 * InnerProd * InnerProd) - 1.f);
}

FVector FQuat::Euler()
{
	return GetRotator().Euler();
}

FVector FQuat::RotateVector(FVector _vector)
{
	FVector _q(X, Y, Z);
	FVector _t = _vector.CrossProduct(_q) * 2.f;
	const FVector _result = _vector + (_t * W) +_q.CrossProduct(_t);
	return _result;
}

FVector FQuat::UnrotateVector(FVector _vector)
{

	FVector _q(-X, -Y, -Z);
	FVector _t =_vector.CrossProduct(_q) * 2.f;
	const FVector _result = _vector + (_t * W) + _q.CrossProduct(_t);
	return _result;
}

FVector FQuat::Vector()
{
	return GetAxisX();
}

FVector FQuat::GetRotationAxis() const
{
	const float _squareSum = X * X + Y * Y + Z * Z;
	if (_squareSum < SMALL_NUMBER)
	{
		return FVector::RightVector;
	}
	const float _scale = FMath::InvSqrt(_squareSum);
	return FVector(X * _scale, Y * _scale, Z * _scale);
	return FVector::ZeroVector;
}

FQuat FQuat::FastLerp(const FQuat& _a, const FQuat& _b, const float _alpha)
{
	const float _dotResult = (_a | _b);
	const float _bias = FMath::FloatSelect(_dotResult, 1.0f, -1.0f);
	return (_b * _alpha) + (_a * (_bias * (1.f - _alpha)));
}

FQuat FQuat::SLerp(const FQuat& _a, const FQuat& _b, const float _slerp)
{
	// Get cosine of angle between quats.
	const float _rawCosom =
		_a.X * _b.X +
		_a.Y * _b.Y +
		_a.Z * _b.Z +
		_a.W * _b.W;
	// Unaligned quats - compensate, results in taking shorter route.
	const float _cosom = FMath::FloatSelect(_rawCosom, _rawCosom, -_rawCosom);

	float _scale0, _scale1;

	if (_cosom < 0.9999f)
	{
		const float _omega = FMath::ACos(_cosom);
		const float _invSin = 1.f / FMath::Sin(_omega);
		_scale0 = FMath::Sin((1.f - _slerp) * _omega) * _invSin;
		_scale1 = FMath::Sin(_slerp * _omega) * _invSin;
	}
	else
	{
		// Use linear interpolation.
		_scale0 = 1.0f - _slerp;
		_scale1 = _slerp;
	}

	// In keeping with our flipped Cosom:
	_scale1 = FMath::FloatSelect(_rawCosom, _scale1, -_scale1);

	FQuat _result;

	_result.X = _scale0 * _a.X + _scale1 * _b.X;
	_result.Y = _scale0 * _a.Y + _scale1 * _b.Y;
	_result.Z = _scale0 * _a.Z + _scale1 * _b.Z;
	_result.W = _scale0 * _a.W + _scale1 * _b.W;

	return _result.GetNormalized();
}

FQuat FQuat::FindBetweenVectors(FVector& _vector1, const FVector& _vector2)
{
	const float _normAB = FMath::Sqrt(_vector1.SquaredLength() * _vector2.SquaredLength());
	return FindBetween_Helper(_vector1, _vector2, _normAB);
}

FQuat FQuat::FindBetweenNormals(FVector& _normal1, const FVector& _normal2)
{
	const float _normAB = 1.f;
	return FindBetween_Helper(_normal1, _normal2, _normAB);
}

FQuat FQuat::FindBetween_Helper(FVector& _a, const FVector& _b, float _normalAB)
{
	float W = _normalAB + _a.DotProduct(_a);
	FQuat _result;

	if (W >= 1e-6f * _normalAB)
	{
		//Result = FVector::CrossProduct(A, B);
		_result = FQuat(
			_a.Y * _b.Z - _a.Z * _b.Y,
			_a.Z * _b.X - _a.X * _b.Z,
			_a.X * _b.Y - _a.Y * _b.X,
			W);
	}
	else
	{
		// A and B point in opposite directions
		W = 0.f;
		const float X = FMath::Abs(_a.X);
		const float Y = FMath::Abs(_a.Y);
		const float Z = FMath::Abs(_a.Z);

		// Find orthogonal basis. 
		const FVector _basis = (X > Y && X > Z) ? FVector::RightVector : -FVector::ForwardVector;

		//Result = FVector::CrossProduct(A, Basis);
		_result = FQuat(
			_a.Y * _basis.Z - _a.Z * _basis.Y,
			_a.Z * _basis.X - _a.X * _basis.Z,
			_a.X * _basis.Y - _a.Y * _basis.X,
			W);
	}

	_result.Normalize();
	return _result;
}

FQuat FQuat::Inverse()
{
	return FQuat(-X, -Y, -Z, W);
}

FQuat FQuat::Log() const
{

	FQuat _result;
	_result.W = 0.f;

	if (FMath::Abs(W) < 1.f)
	{
		const float _angle = FMath::ACos(W);
		const float _sinAngle = FMath::Sin(_angle);

		if (FMath::Abs(_sinAngle) >= 1.e-8f)
		{
			const float _scale = _angle / _sinAngle;
			_result.X = _scale * X;
			_result.Y = _scale * Y;
			_result.Z = _scale * Z;

			return _result;
		}
	}

	_result.X = X;
	_result.Y = Y;
	_result.Z = Z;

	return _result;
}

FQuat FQuat::MakeFromEuler(FVector& _euler)
{
	return FQuat(FRotator::MakeFromEuler(_euler));
}

FString FQuat::ToString()
{
	return FString::Format("X={} Y={} Z={} W={}", X, Y, Z,W);
}

void FQuat::Normalize(float _tolerance)
{
	const float _squareSum = X * X + Y * Y + Z * Z + W * W;

	if (_squareSum >= _tolerance)
	{
		const float _scale = FMath::InvSqrt(_squareSum);

		X *= _scale;
		Y *= _scale;
		Z *= _scale;
		W *= _scale;
	}
	else
	{
		*this = FQuat::Identity;
	}
}

void FQuat::ToAxisAndAngle(FVector& _axis, float& _angle) const
{
	_angle = GetAngle();
	_axis = GetRotationAxis();
}

FQuat FQuat::operator+(const FQuat& _q) const
{
	return FQuat(X + _q.X, Y + _q.Y, Z + _q.Z, W + _q.W);
}

FQuat FQuat::operator+=(const FQuat& _q)
{
	this->X += _q.X;
	this->Y += _q.Y;
	this->Z += _q.Z;
	this->W += _q.W;
	return *this;
}

FQuat FQuat::operator-(const FQuat& _q) const
{
	return FQuat(X - _q.X, Y - _q.Y, Z - _q.Z, W - _q.W);
}

FQuat FQuat::operator-() const
{
	return FQuat(-X, -Y, -Z, -W);
}

FQuat FQuat::operator-=(const FQuat& _q)
{
	this->X -= _q.X;
	this->Y -= _q.Y;
	this->Z -= _q.Z;
	this->W -= _q.W;
	return *this;
}

FQuat FQuat::operator*(const FQuat& _q) const
{
	return FQuat(X * _q.X, Y * _q.Y, Z * _q.Z, W * _q.W);
}

FQuat FQuat::operator*(const float& _float) const
{
	return operator*(FQuat(_float,_float,_float,1));
}

FQuat FQuat::operator*=(const FQuat& _q)
{
	this->X *= _q.X;
	this->Y *= _q.Y;
	this->Z *= _q.Z;
	this->W *= _q.W;
	return *this;
}

bool FQuat::operator==(const FQuat& _q) const
{
	return X == _q.X && Y == _q.Y && Z == _q.Z && W == _q.W;
}

bool FQuat::operator!=(const FQuat& _q) const
{
	return X != _q.X || Y != _q.Y || Z != _q.Z || W != _q.W;
}

float FQuat::operator|(const FQuat& _q) const
{
	return X * _q.X + Y * _q.Y + Z * _q.Z + W * _q.W;
}
