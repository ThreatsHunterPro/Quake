#pragma once 
#include "../../Containers/FString.h"
struct FVector2
{
	float X;
	float Y;

	static FVector2 ZeroVector;
	static FVector2 UnitVector;
	static FVector2 Unit45Deg;


public:
	FVector2();
	/// <summary>
	/// X,Y are Equals
	/// </summary>
	/// <param name="_value"></param>
	FVector2(float _value);
	FVector2(float _x, float _y);
	FVector2(const FVector2& _other);

public:
	static float CrossProduct(const FVector2& _a, const FVector2& _b);
	static float Distance(const FVector2& _a, const FVector2& _b);
	static float DistSquared(const FVector2& _a, const FVector2& _b);
	static float DotProduct(const FVector2& _a, const FVector2& _b);
	float Length() const;
	float SquaredLength() const;
	bool Normalize(float _tolerance);
	FVector2 GetSafeNormal(float _tolerance) const;
	FString ToString() const;

	FVector2 operator+(const FVector2& _other) const;
	FVector2 operator+(float _a) const;
	FVector2 operator-(const FVector2& _other) const;
	FVector2 operator-(float _a) const;
	FVector2 operator*(const FVector2& _other) const;
	FVector2 operator*(float _scale) const;
	FVector2 operator/(const FVector2& _other) const;
	FVector2 operator/(float _scale) const;

	float operator|(const FVector2& _other) const;
	float operator^(const FVector2& _other) const;

public:

	bool operator==(const FVector2& _other) const;
	bool operator!=(const FVector2& _other) const;
	FVector2 operator-() const;
	FVector2 operator+=(const FVector2& _other);
	FVector2 operator+=(const float& _a);
	FVector2 operator-=(const FVector2& _other);
	FVector2 operator-=(const float& _a);
	FVector2 operator*=(const FVector2& _other);
	FVector2 operator*=(float _scale);
	FVector2 operator/=(const FVector2& _other);
	FVector2 operator/=(float _a);
	float& operator[](int Index);
	float operator[](int Index) const;
};