#include "CustomShader.h"
#include "Source/common/shader.hpp"

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
	shaderProgramID = LoadShaders(_vertexPath, _fragmentPath);
}

void CustomShader::SetBool(const string& _name, const bool _value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramID, _name.c_str()), (int)_value);
}

void CustomShader::SetInt(const string& _name, const int _value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramID, _name.c_str()), _value);
}

void CustomShader::SetFloat(const string& _name, const float _value) const
{
	glUniform1f(glGetUniformLocation(shaderProgramID, _name.c_str()), _value);
}

void CustomShader::SetVec3(const string& _name, const vec3& _value) const
{
	glUniform3f(glGetUniformLocation(shaderProgramID, _name.c_str()), _value.x, _value.y, _value.z);
}

void CustomShader::SetVec4(const string& _name, const vec4& _value) const
{
	glUniform4f(glGetUniformLocation(shaderProgramID, _name.c_str()), _value.x, _value.y, _value.z, _value.w);
}

void CustomShader::SetMat4(const string& _name, const mat4& _model) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, _name.c_str()), 1, GL_FALSE, &_model[0][0]);
}