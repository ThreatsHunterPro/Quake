#include "FMath.h"
#include "FVector/TVector.h"
#include <iostream>

float FMath::RandRange(float _inMin, float _inMax)
{
	return _inMin + (_inMax - _inMin) * std::rand() /** FRand()*/;
}
float FMath::FInterpConstantTo(float _current, float _target, float _deltaTime, float _interpSpeed)
{
	const float _dist = _target - _current;

	if (FMath::Square(_dist) < SMALL_NUMBER)
		return _target;

	const float _step = _interpSpeed * _deltaTime;
	return _current + FMath::Clamp(_dist, -_step, _step);
}
FVector FMath::VInterpConstantTo(FVector& _current, FVector& _target, float _deltaTime, float _interpSpeed)
{
	FVector _delta = _target - _current;
	const float _deltaM = _delta.Length();
	const float _maxStep = _interpSpeed * _deltaTime;

	if (_deltaM > _maxStep)
	{
		if (_maxStep > 0.f)
		{
			FVector _deltaN = _delta / _deltaM;
			return _current + _deltaN * _maxStep;
		}
		else
			return _current;
	}
	return _target;
}
float FMath::InvSqrt(const float& _scale)
{
	long _i;
	float _x2, _y;
	const float _threehalfs = 1.5F;

	_x2 = _scale * 0.5F;
	_y = _scale;
	_i = *(long*)&_y; // evil floating point bit level hacking
	_i = 0x5f3759df - (_i >> 1); // what the fuck?
	_y = *(float*)&_i;
	_y = _y * (_threehalfs - (_x2 * _y * _y)); // 1st iteration
	//	_y = _y * ( threehalfs - ( _x2 * _y * _y ) ); // 2nd iteration, this can be removed

	return _y;
}
