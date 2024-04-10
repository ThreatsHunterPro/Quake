#pragma once 
#include "..\..\..\CoreMinimal.h"
#include "FMath.h"
#include "FVector/FVector4.h"

namespace EAxis
{
	enum Type : int
	{
		None,
		X,
		Y,
		Z
	};
}
struct FMatrix
{
#pragma region Var
	float M[4][4];
	static FMatrix Identity;
#pragma endregion

#pragma region Constructor
	FMatrix();
	FMatrix(const FVector& _inX, const FVector& _inY, const FVector& _inZ, const FVector& _inW);
	FMatrix(const FVector4& _inX, const FVector4& _inY, const FVector4& _inZ, const FVector4& _inW);
	FMatrix(const mat3& _matrix3);
#pragma endregion

#pragma region Methods
	void SetIdentity();
	void RemoveScaling(float _tolerance = SMALL_NUMBER);
	void ScaleTranslation(const FVector& _inScale3D);
	void GetScaledAxes(FVector& _x, FVector& _y, FVector& _z) const;
	void GetUnitAxes(FVector& _x, FVector& _y, FVector& _z) const;
	void SetAxis(int _index, const FVector& Axis);
	void SetOrigin(const FVector& _newOrigin);
	void SetAxes(const FVector* _axis0 = NULL, const FVector* _axis1 = NULL, const FVector* _axis2 = NULL, const FVector* _origin = NULL);
	void SetColumn(int _index, FVector _value);
	void Mirror(EAxis::Type _mirrorAxis, EAxis::Type _flipAxis);
	void VectorMatrixMultiply(FMatrix* _result, const FMatrix* _matrix1, const FMatrix* _matrix2);
	void VectorMatrixMultiply(FMatrix* _result, const FMatrix* _matrix1, const mat4* _matrix2);


	bool Equals(const FMatrix& _other, float _tolerance = KINDA_SMALL_NUMBER) const;

	float Determinant() const;
	float RotDeterminant() const;
	float GetMinimumAxisScale() const;
	float GetMaximumAxisScale() const;

	FVector ExtractScaling(float _tolerance = SMALL_NUMBER);
	FVector GetScaleVector(float _tolerance = SMALL_NUMBER);
	FVector GetColumn(int _index) const;
	FVector GetOrigin() const;
	FVector GetScaledAxis(EAxis::Type _inAxis) const;
	FVector GetUnitAxis(EAxis::Type _inAxis) const;

	FMatrix GetTransposed() const;
	FMatrix TransposeAdjoint() const;
	FMatrix GetMatrixWithoutScale(float _tolerance = SMALL_NUMBER) const;
	FMatrix RemoveTranslation() const;
	FMatrix ConcatTranslation(const FVector& _translation) const;
	FMatrix ApplyScale(float _scale) const;

	FString ToString() const;

	mat4 ToMat4();
	const mat4 ToMat4()const ;
#pragma endregion

#pragma region Operators
	FMatrix	operator+(const FMatrix& _other) const;
	FMatrix	operator+(const mat4& _other) const;
	void operator+=(const FMatrix& _other);
	void operator+=(const mat4& _other);
	FMatrix operator*(const FMatrix& _other);
	FMatrix operator*(const mat4& _other);
	FMatrix operator*(float _other) const;
	void operator*=(const FMatrix& _other); 
	void operator*=(const mat4& _other);
	void operator*=(float _other);
	bool operator==(const FMatrix& _other) const;
	bool operator==(const mat4& _other) const;
	bool operator!=(const FMatrix& _other) const;
	bool operator!=(const mat4& _other) const;
	FMatrix operator=(const FMatrix& _other);
	FMatrix operator=(const mat4& _other);

#pragma endregion

};

