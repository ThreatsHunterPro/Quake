#include "FRotator.h"
#include "FVector/TVector.h"

FRotator::FRotator()
{
	Pitch = 0;
	Yaw = 0;
	Roll = 0;
}

FRotator::FRotator(float _inPitch, float _inYaw, float _inRoll)
{
	Pitch = _inPitch;
	Yaw = _inYaw;
	Roll = _inRoll;
}

FVector FRotator::Euler()const
{
	return FVector(Roll, Pitch, Yaw);
}

FRotator FRotator::MakeFromEuler(const FVector& _euler)
{
	return FRotator(_euler.Y, _euler.Z, _euler.X);
}

FRotator FRotator::Add(float _pitch, float _yaw, float _roll)
{
	FRotator _rota = *this;
	_rota.Pitch += _pitch;
	_rota.Yaw += _yaw;
	_rota.Roll += _roll;
	return _rota;
}

bool FRotator::Equals(const FRotator& _rota, float _tolerance)
{
	const float _pitch = abs(NormalizeAxis(Pitch - _rota.Pitch));
	const float _yaw = abs(NormalizeAxis(Yaw - _rota.Yaw));
	const float _roll = abs(NormalizeAxis(Roll - _rota.Roll));
	
	return _pitch <= _tolerance && _yaw <= _tolerance && _roll <= _tolerance;
}

void FRotator::Normalize()
{
	Pitch = NormalizeAxis(Pitch);
	Yaw = NormalizeAxis(Yaw);
	Roll = NormalizeAxis(Roll);
}

float FRotator::NormalizeAxis(const float& _angle)const
{
	float _angleClamp = ClampAxis(_angle);
	if (_angleClamp > 180)
		_angleClamp -= 360;

	return _angleClamp;
}

FRotator FRotator::Clamp()
{
	Pitch = ClampAxis(Pitch);
	Yaw = ClampAxis(Yaw);
	Roll = ClampAxis(Roll);
	return *this;
}

float FRotator::ClampAxis(float _angle) const
{
	return std::fmod(_angle, 360);
}

FRotator FRotator::GetNormalize() const
{
	FRotator _rota = *this;
	_rota.Normalize();
	return _rota;
}

FString FRotator::ToString()
{
	return FString::Format("Pitch={} Yaw={} Roll={}", Pitch, Yaw, Roll);
}

FRotator FRotator::operator-(const FRotator& _temp)
{
	FRotator _result = *this;
	_result.Pitch -= _temp.Pitch;
	_result.Yaw -= _temp.Yaw;
	_result.Roll -= _temp.Roll;
	return _result;
}

FRotator FRotator::operator+(const FRotator& _temp)
{
	FRotator _result = *this;
	_result.Pitch += _temp.Pitch;
	_result.Yaw += _temp.Yaw;
	_result.Roll += _temp.Roll;
	return _result;
}

FRotator FRotator::operator+=(const FRotator& _temp)
{
	Pitch += _temp.Pitch;
	Yaw += _temp.Yaw;
	Roll += _temp.Roll;
	return *this;
}

FRotator FRotator::operator-=(const FRotator& _temp)
{
	Pitch -= _temp.Pitch;
	Yaw -= _temp.Yaw;
	Roll -= _temp.Roll;
	return *this;
}

FRotator FRotator::operator*(const float& _scale)
{
	FRotator _result = *this;
	_result.Pitch *= _scale;
	_result.Yaw *= _scale;
	_result.Roll *= _scale;
	return _result;
}

FRotator FRotator::operator*=(const float& _scale)
{
	Pitch *= _scale;
	Yaw *= _scale;
	Roll *= _scale;
	return *this;
}

bool FRotator::operator==(const FRotator& _temp)
{
	return Pitch == _temp.Pitch && Yaw == _temp.Yaw && Roll == _temp.Roll;
}

bool FRotator::operator!=(const FRotator& _temp)
{
	return Pitch != _temp.Pitch || Yaw != _temp.Yaw || Roll != _temp.Roll;
}
