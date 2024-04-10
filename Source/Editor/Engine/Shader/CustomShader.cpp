#include "CustomShader.h"
#include "Source/common/shader.hpp"
#include "Source\Runtime\Core\Math\FVector\TVector.h"

CustomShader::CustomShader()
{
	shaderProgramID = 0;
}


void CustomShader::Use() const
{
	glUseProgram(shaderProgramID);
}

void CustomShader::ClearShader() const
{
	glDeleteProgram(shaderProgramID);
}

void CustomShader::LoadShadersFromPath(const char* _vertexPath, const char* _fragmentPath)
{
	shaderProgramID = LoadShaders(GetShader(_vertexPath).c_str(), GetShader(_fragmentPath).c_str());
}

string CustomShader::GetShader(const char* _path)
{
	return FString::Format("../Content/Shaders/{}",_path).GetText();
	//return string("../Content/Shaders/") + string(_path);
}

void CustomShader::SetBool(const FString& _name, const bool _value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramID, _name.GetText().c_str()), (int)_value);
}

void CustomShader::SetInt(const FString& _name, const int _value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramID, _name.GetText().c_str()), _value);
}

void CustomShader::SetFloat(const FString& _name, const float _value) const
{
	glUniform1f(glGetUniformLocation(shaderProgramID, _name.GetText().c_str()), _value);
}

void CustomShader::SetVec3(const FString& _name, const FVector& _value) const
{
	glUniform3f(glGetUniformLocation(shaderProgramID, _name.GetText().c_str()), _value.X, _value.Y, _value.Z);
}

void CustomShader::SetVec4(const FString& _name, const FVector4& _value) const
{
	glUniform4f(glGetUniformLocation(shaderProgramID, _name.GetText().c_str()), _value.X, _value.Y, _value.Z, _value.W);
}

void CustomShader::SetMat4(const FString& _name, FMatrix& _model) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, _name.GetText().c_str()), 1, GL_FALSE, &_model.ToMat4()[0][0]);
}