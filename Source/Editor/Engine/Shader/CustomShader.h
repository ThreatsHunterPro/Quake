#pragma once
#include "Source/CoreMinimal.h"
#include "Source/Runtime/Core/Math/FMatrix.h"
#include "Source/Runtime/Core/Math/FVector/FVector4.h"
#include "Source/Runtime/Core/Containers/FString.h"

class CustomShader
{
	int shaderProgramID;
	
public:
	FORCEINLINE int GetShaderID() const { return shaderProgramID; }

public:
	CustomShader();

public:
	void Use() const;
	void ClearShader() const;

	void LoadShadersFromPath(const char* _vertexPath, const char* _fragmentPath);
	string GetShader(const char* _path);
	void SetBool(const FString& _name, const bool _value) const;
	void SetInt(const FString& _name, const int _value) const;
	void SetFloat(const FString& _name, const float _value) const;
	void SetVec3(const FString& _name, const FVector& _value) const;
	void SetVec4(const FString& _name, FVector4& _value) const;
	void SetMat4(const FString& _name, FMatrix& _model) const;
};