#pragma once 
#include "..\..\..\..\CoreMinimal.h"
#include "FVector2.h"
#include "../FRotator.h"
#include "../Quat.h"
#include "../FMath.h"

struct FVector4
{
#pragma region Var
	float W;
	float X;
	float Y;
	float Z;

	static FVector4 ZeroVector;
	static FVector4 One;
#pragma endregion Var
public:
	FVector4();
	FVector4(float _a);
	FVector4(const FVector4& InVector);
	FVector4(const FVector& InVector, float InW);
	FVector4(FVector2 InXY, FVector2 InZW);
	FVector4(float InX, float InY, float InZ, float InW);

	bool Equals(const FVector4& _other, float _tolerance) const;
	FString ToString() const;
	FVector4 GetSafeNormal(float _tolerance) const;
	FVector4 GetUnsafeNormal3() const;
	FQuat ToOrientationQuat() const;
	FRotator ToOrientationRotator() const;
	FRotator Rotation() const;

	float Size3() const;
	float SizeSquared3() const;
	float Size() const;
	float SizeSquared() const;

	float Dot3(const FVector4& _vec1, const FVector4& _vec2);
	float Dot3(const FVector4& _vec1, const FVector& _vec2);
	float Dot4(const FVector4& _vec1, const FVector4& _vec2);

	FVector4 operator-(const FVector4& _v);
	const FVector4 operator-();
	const bool operator!=(const FVector4& _v);
	const bool operator==(const FVector4& _v);
	const FVector4 	operator*(const FVector4& _v);
	const FVector4 	operator*(float _scale);
	FVector4 operator*=(float _s);
	FVector4 operator*=(const FVector4& _v);
	const FVector4 	operator/(float _scale);
	const FVector4 	operator/(const FVector4& _v);
	FVector4 operator/=(const FVector4& _v);
	const FVector4 	operator^(const FVector4& _v);
	const FVector4 	operator+(const FVector4& _v);
	FVector4 operator+=(const FVector4& _v);
	FVector4 operator-=(const FVector4& _v);
};