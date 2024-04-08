#pragma once
#include"..\..\..\CoreMinimal.h"

#define PI 3.1415926535897932f
#define TWO_PI 6.28318530717f
#define SMALL_NUMBER 1.e-8f
#define KINDA_SMALL_NUMBER 1.e-4f
#define NULL 0

class FMath
{
public:
	static float RandRange(float _inMin, float _inMax);
	static float FInterpConstantTo(float _current, float _target, float _deltaTime, float _interpSpeed);
	static FVector VInterpConstantTo(FVector& _current, FVector& _target, float _deltaTime, float _interpSpeed);

	template <typename T>
	static float DegreesToRadians(const T& _degVal)
	{
		return _degVal * (PI / 180.f);
	}
	template <typename T>
	static float RadiansToDegrees(const T& _radVal)
	{
		return _radVal * (180.f / PI);
	}
	template <typename T>
	static T DivideAndRoundUp(T _dividend, T _divisor)
	{
		return (_dividend + _divisor - 1) / _divisor;
	}
	template <typename T>
	static T DivideAndRoundDown(T _dividend, T _divisor)
	{
		return _dividend / _divisor;
	}
	template <typename T>
	static T DivideAndRoundNearest(T _dividend, T _divisor)
	{
		return (_dividend >= 0) ? (_dividend + _divisor / 2) / _divisor : (_dividend - _divisor / 2 + 1) / _divisor;
	}
	template <typename T, typename U>
	static T Lerp(const T& _a, const T& _b, const U& _alpha)
	{
		return (T)((_a * (1.0 - _alpha)) + (_b * _alpha));
	}
	template <typename T>
	static T Clamp(const T _x, const T _min, const T _max)
	{
		return Max(Min(_x, _max), _min);
	}
	template <typename T>
	static T Square(const T _a)
	{
		return _a * _a;
	}
	template <typename T>
	static T Max(const T _a, const T _b)
	{
		return (_b < _a) ? _a : _b;
	}
	template <typename T>
	static T Min(const T _a, const T _b)
	{
		return (_a < _b) ? _a : _b;
	}
	static float UnwindRadians(float _a)
	{
		while (_a > PI)
		{
			_a -= TWO_PI;
		}
		while (_a < -PI)
		{
			_a += TWO_PI;
		}
		return _a;
	}
	static float Cos(float _a)
	{
		return cos(_a);
	}
	static float Sin(float _a)
	{
		return sin(_a);
	}
	static float ASin(float _a)
	{
		return asin(_a);
	}
	static float ACos(float _a)
	{
		return acos(_a);
	}
	static float Tan(float _a)
	{
		return tan(_a);
	}
	static float ATan(float _a)
	{
		return atan(_a);
	}
	static float ATan2(float _a,float _b)
	{
		return atan2(_a, _b);
	}
	static float Sqrt(float _a)
	{
		return sqrt(_a);
	}
	static float Abs(float _a)
	{
		return abs(_a);
	}
	static float FloatSelect(float Comparand, float ValueGEZero, float ValueLTZero)
	{
		return Comparand >= 0.f ? ValueGEZero : ValueLTZero;
	}
	static float InvSqrt(const float& _scale);
	static void SinCos(float* _scalarSin, float* _scalarCos, float _value)
	{
		// No approximations for doubles
		*_scalarSin = FMath::Sin(_value);
		*_scalarCos = FMath::Cos(_value);
	}
};