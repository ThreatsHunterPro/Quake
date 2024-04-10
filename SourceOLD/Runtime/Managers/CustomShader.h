#pragma once
#include "Source/CoreMinimal.h"

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
	void SetBool(const string& _name, const bool _value) const;
	void SetInt(const string& _name, const int _value) const;
	void SetFloat(const string& _name, const float _value) const;
	void SetVec3(const string& _name, const vec3& _value) const;
	void SetVec4(const string& _name, const vec4& _value) const;
	void SetMat4(const string& _name, const mat4& _model) const;
};