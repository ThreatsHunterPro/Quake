#pragma once
#include "../Containers/FString.h"
#include "..\..\..\CoreMinimal.h"
struct FRotator
{
	float Pitch;
	float Roll;
	float Yaw;

public:
	FRotator();
	FRotator(float _inPitch, float _inYaw, float _inRoll);

public:
	FVector Euler()const;
	static FRotator MakeFromEuler(const FVector& _euler);
	
	FRotator Add(float _pitch, float _yaw, float _roll);

	bool Equals(const FRotator& _rota, float _tolerance);
#pragma region Normalize
	void Normalize();
	float NormalizeAxis(const float& _angle)const;
	FRotator GetNormalize()const;
#pragma endregion

#pragma region Clamp
	FRotator Clamp();
	float ClampAxis(const float _angle)const;
#pragma endregion

	FString ToString();

public:
#pragma region Operators
	FRotator operator-(const FRotator& _temp);
	FRotator operator+(const FRotator& _temp);

	FRotator operator+=(const FRotator& _temp);
	FRotator operator-=(const FRotator& _temp);

	FRotator operator*(const float& _scale);
	FRotator operator*=(const float& _scale);

	bool operator==(const FRotator& _temp);
	bool operator!=(const FRotator& _temp);
#pragma endregion
};

