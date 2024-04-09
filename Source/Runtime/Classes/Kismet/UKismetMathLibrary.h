#pragma once
#include <iostream>
#include <vector>

#define Kismet_PI 3.141592653589793f

class UKismetMathLibrary
{
public:

	static float Abs(float _value);
	static int Abs_Int(int _value);
	static float ACos(float _value);
	static float ASin(float _value);
	static float Cos(float _value);
	static int BMax(int _a, int _b);
	static int BMin(int _a, int _b);
	static float Clamp(float _value, float _min, float _max);
	static int ClampInt(int _value, int _min, int _max);
	static double ClampAngle(double _angleDeg , double _minDeg, double _maxDeg);
	static float ClampAxis(float _angle);
	//static float ClampAxes2D(FVector2D _vector, double MinAxisVal, double MaxAxisVal);
	//static FVector ClampVectorSize(FVector A, double Min, double Max);
	//static float CrossProduct2D(FVector2D A, FVector2D B);
	//static FVector Cross_VectorVector(FVector A, FVector B);
	static float DegACos(float _value);
	static float DegASin(float _value);
	static float DegATan(float _value);
	static float DegATan2(float _a, float _b);
	static float DegCos(float _value);
	static float DegToRadians(float _value);
	static float DegSin(float _value);
	static float DegTan(float _value);
	//static float Distance2D(FVector2D _v1 , FVector2D _v2);
	//static float DistanceSquared2D(FVector2D _v1, FVector2D _v2);
	//static float DotProduct2D(FVector2D _v1, FVector2D _v2);
	static double FClamp(double _value, double _min, double _max);
	static int FFloor(double _value);
	//static FRotator FindLookAtRotation(const FVector& Start, const FVector& Target);
	//static FRotator MakeRotFromX(const FVector& X)
	static double FInterpTo(double _current, double _target, double _deltaTime, double _interpSpeed);
	static double FMax(double _a, double _b);
	static double FMin(double _a, double _b);
	//static FVector2D GetAbs2D(FVector2D _vector);
	//static double GetAbsMax2D(FVector2D _vector);
	static double Lerp(double _a, double _b, double _alpha);
	static double Log(double _a, double _base);
	static float Max(float _a, float _b);
	static int MaxInt(int _a, int _b);
	static float Min(float _a, float _b);
	static int MinInt(int _a, int _b);
	//static FVector Normal(FVector A, float Tolerance)
	//static FVector2D Normal2D(FVector2D _a);

};

