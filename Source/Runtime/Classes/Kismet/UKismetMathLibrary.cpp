#include "UKismetMathLibrary.h"
#include "../../Core/Math/FMath.h"

float UKismetMathLibrary::Abs(float _value)
{
	return std::fabs(_value);
}

int UKismetMathLibrary::Abs_Int(int _value)
{
	return std::abs(_value);
}

float UKismetMathLibrary::ACos(float _value)
{
	return std::acos(_value);
}

float UKismetMathLibrary::ASin(float _value)
{
	return std::asin(_value);
}

float UKismetMathLibrary::Cos(float _value)
{
	return std::cos(_value);
}

int UKismetMathLibrary::BMax(int _a, int _b)
{
	int _value = (_a > _b)? _a : _b;
	return _value;
}

int UKismetMathLibrary::BMin(int _a, int _b)
{
	int _value = (_a < _b) ? _a : _b;
	return _value;
}

float UKismetMathLibrary::Clamp(float _value, float _min, float _max)
{
	return FMath::Clamp(_value, _min, _max);
}

int UKismetMathLibrary::ClampInt(int _value,int _min, int _max)
{
	return FMath::Clamp(_value, _min, _max);

}

double UKismetMathLibrary::ClampAngle(double _angleDeg, double _minDeg, double _maxDeg)
{
	return FMath::Clamp((double)_angleDeg,(double) _minDeg, (double)_maxDeg);
}


//float UKismetMathLibrary::ClampAxes2D(FVector2D _vector, double MinAxisVal, double MaxAxisVal)
//{
//	return _vector.ClampAxes(MinAxisVal, MaxAxisVal);
//}

float UKismetMathLibrary::ClampAxis(float _angle)
{
	return ClampAngle(_angle, 0, 360);
}


//FVector UKismetMathLibrary::ClampVectorSize(FVector A, double Min, double Max)
//{
//	return A.GetClampedToSize(Min, Max);
//}
//
//float UKismetMathLibrary::CrossProduct2D(FVector2D A, FVector2D B)
//{
//	return FVector2D::CrossProduct(A, B);
//}
//
//FVector UKismetMathLibrary::Cross_VectorVector(FVector A, FVector B)
//{
//	return FVector::CrossProduct(A, B);
//}
//
//
//float UKismetMathLibrary::Distance2D(FVector2D _v1, FVector2D _v2)
//{
//	return FVector2D::Distance(_v1, _v2);
//}
//float UKismetMathLibrary::DistanceSquared2D(FVector2D _v1, FVector2D _v2)
//{
//	return FVector2D::DistSquared(_v1, _v2);
//}
//float UKismetMathLibrary::DotProduct2D(FVector2D _v1, FVector2D _v2)
//{
//	return FVector2D::DotProduct(_v1, _v2);
//}

float UKismetMathLibrary::DegACos(float _value)
{
	return 180.0f/ Kismet_PI * std::acos(_value);
}

float UKismetMathLibrary::DegASin(float _value)
{
	return 180.0f/ Kismet_PI * std::asin(_value);
}

float UKismetMathLibrary::DegATan(float _value)
{
	return 180.0f / Kismet_PI * std::atan(_value);
}

float UKismetMathLibrary::DegATan2(float _a, float _b)
{
	return 180.0f / Kismet_PI * std::atan2(_a, _b);
}

float UKismetMathLibrary::DegCos(float _value)
{
	return std::cos(Kismet_PI / (180.0f) * _value);
}

float UKismetMathLibrary::DegToRadians(float _value)
{
	return _value * (Kismet_PI/180.0f);
}

float UKismetMathLibrary::DegSin(float _value)
{
	return std::sin(Kismet_PI / (180.0f) * _value);
}

float UKismetMathLibrary::DegTan(float _value)
{
	return std::tan(Kismet_PI / (180.0f) * _value);
}

double UKismetMathLibrary::FClamp(double _value, double _min, double _max)
{
	return Clamp(_value, _min, _max);
}

int UKismetMathLibrary::FFloor(double _value)
{
	return (int)std::floor(_value);
}

//FRotator UKismetMathLibrary::FindLookAtRotation(const FVector& Start, const FVector& Target)
//{
//	return MakeRotFromX(Target - Start);
//}
//
//FRotator UKismetMathLibrary::MakeRotFromX(const FVector& X)
//{
//	return FRotationMatrix::MakeFromX(X).Rotator();
//}

double UKismetMathLibrary::FInterpTo(double _current, double _target, double _deltaTime, double _interpSpeed)
{

	return FMath::FInterpConstantTo(_current,_target,_deltaTime,_interpSpeed);

}

double UKismetMathLibrary::FMax(double _a, double _b)
{
	return BMax(_a, _b);
}

double UKismetMathLibrary::FMin(double _a, double _b)
{
	return BMin(_a, _b);
}
//
//FVector2D UKismetMathLibrary::GetAbs2D(FVector2D _vector)
//{
//	return _vector.GetAbs();
//}
//double UKismetMathLibrary::GetAbsMax2D(FVector2D _vector)
//{
//	return _vector.GetAbsMax();
//}


double UKismetMathLibrary::Lerp(double _a, double _b, double _alpha)
{
	return _a + _alpha * (_b - _a);
}

double UKismetMathLibrary::Log(double _a, double _base)
{
	double Result = 0.f;
	if (_base <= 0.f)
		std::cout << "Divide by zero: Log" << std::endl;
	else
		Result = std::log(_a) / std::log(_base);

	return Result;
}

float UKismetMathLibrary::Max(float _a, float _b)
{
	float _value = (_a > _b) ? _a : _b;
	return _value;
}

int UKismetMathLibrary::MaxInt(int _a, int _b)
{
	return BMax(_a, _b);
}

float UKismetMathLibrary::Min(float _a, float _b)
{
	float _value = (_a < _b) ? _a : _b;
	return _value;
}

int UKismetMathLibrary::MinInt(int _a, int _b)
{
	return BMin(_a, _b);
}

//FVector UKismetMathLibrary::Normal(FVector A, float Tolerance)
//{
//	return A.GetSafeNormal(Tolerance);
//}
//
//FVector2D UKismetMathLibrary::Normal2D(FVector2D _a);
//{
//	return _a.GetSafeNormal()
//}

