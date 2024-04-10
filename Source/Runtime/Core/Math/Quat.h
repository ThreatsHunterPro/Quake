#pragma once
#include "../Containers/FString.h"
#include "FMath.h"
#include "FRotator.h"

struct FQuat
{
	float W;
	float X;
	float Y;
	float Z;
	static FQuat Identity;


public:
	FQuat() = default;
	FQuat(const FRotator& _rotator);
	FQuat(FRotator _axis, float _angleRad);
	FQuat(float _x, float _y, float _z, float _w);
public:
	float GetAngle() const;
	float GetTwistAngle(FVector& _twistAxis) const;
	float Size() const;
	float SizeSquared() const; /*C'est au ²*/
	FVector GetAxisX();
	FVector GetAxisY();
	FVector GetAxisZ();
	FVector GetForwardVector();
	FVector GetRightVector();
	FVector GetUpVector();
	FQuat GetNormalized(float _tolerance = SMALL_NUMBER) const;
	FRotator GetRotator() const;




public:
	bool Equals(const FQuat& _other, float _tolerance);
	bool IsIdentity(float _tolerence = SMALL_NUMBER);
	bool IsNormalized();



public:
	float AngularDistance(const FQuat& _quat) const;
	
	FVector Euler();
	FVector RotateVector(FVector _vector);
	FVector UnrotateVector(FVector _vector);
	FVector Vector();
	FVector GetRotationAxis() const;
	FQuat FastLerp(const FQuat& _a, const FQuat& _b, const float _alpha);
	FQuat SLerp(const FQuat& _a, const FQuat& _b, const float _slerp);
	FQuat FindBetweenVectors(FVector& _vector1, const FVector& _vector2);
	FQuat FindBetweenNormals(FVector& _normal1, const FVector& _normal2);
	FQuat FindBetween_Helper(FVector& _a, const FVector& _b, float _normalAB);
	FQuat Inverse();
	FQuat Log()const;
	FQuat MakeFromEuler(FVector& _euler) ;
	FString ToString();


public:
	void Normalize(float _tolerance = SMALL_NUMBER);
	void ToAxisAndAngle(FVector& _axis, float& _angle) const;

public:
	FQuat operator+(const FQuat& _q) const;
	FQuat operator+=(const FQuat& _q);
	FQuat operator-(const FQuat& _q) const;
	FQuat operator-() const;
	FQuat operator-=(const FQuat& _q);
	FQuat operator*(const FQuat& _q) const;
	FQuat operator*(const float& _float) const;
	FQuat operator*=(const FQuat& _q);
	//FQuat operator*(const float _scale,const FQuat& _q);
	bool operator==(const FQuat& _q) const;
	bool operator!=(const FQuat& _q) const;
	float operator|(const FQuat& _q) const;


};

