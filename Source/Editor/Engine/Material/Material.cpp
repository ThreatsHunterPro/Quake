#include "Material.h"



#define STB_IMAGE_IMPLEMENTATION

#pragma region Constructor

UMaterial::UMaterial()
{
	shininess = 32.0f;
}

UMaterial::UMaterial(const char* _vertexPath, const char* _fragmentPath)
{
	LoadMaterialShader(_vertexPath, _fragmentPath);
	shininess = 32.0f;
}

#pragma endregion


#pragma region LoadInit

void UMaterial::InitMaterialTextures()
{
	materialShader.Use();
	materialShader.SetInt("material.diffuse", 0);
	materialShader.SetInt("material.specular", 1);
	materialShader.SetInt("material.emission", 2);
}

void UMaterial::BindAndUseMaterialTextures()
{
	materialShader.Use();

	diffuseTexture.BindTexture(0);
	specularTexture.BindTexture(1);
	emissionTexture.BindTexture(2);
}

void UMaterial::SetLightValues(FVector _ambientValue, FVector _diffuseValue, FVector _specularValue)
{
	SetAmbientValue(_ambientValue);
	SetDiffuseValue(_diffuseValue);
	SetSpecularValue(_specularValue);
}

void UMaterial::LoadMaterialShader(const char* _vertexPath, const char* _fragmentPath)
{
	materialShader.LoadShadersFromPath(_vertexPath, _fragmentPath);
}

void UMaterial::LoadDiffuseTexture(const char* _texturePath, int _wrapParam, int _filterParam)
{
	diffuseTexture.LoadTexture(_texturePath, _wrapParam, _filterParam);
}

void UMaterial::LoadSpecularTexture(const char* _texturePath, int _wrapParam, int _filterParam)
{
	specularTexture.LoadTexture(_texturePath, _wrapParam, _filterParam);
}

void UMaterial::LoadEmissionTexture(const char* _texturePath, int _wrapParam, int _filterParam)
{
	emissionTexture.LoadTexture(_texturePath, _wrapParam, _filterParam);
}

#pragma region Set


void UMaterial::SetAmbientValue(FVector _ambientValue)
{
	ambientValue = _ambientValue;
	materialShader.SetVec3("light.ambient", ambientValue);
}

void UMaterial::SetDiffuseValue(FVector _diffuseValue)
{
	diffuseValue = _diffuseValue; diffuseValue;
	materialShader.SetVec3("light.diffuse", diffuseValue);
}

void UMaterial::SetSpecularValue(FVector _specularValue)
{
	specularValue = _specularValue; specularValue;
	materialShader.SetVec3("light.specular", specularValue);
}

void UMaterial::SetShininessValue(float _shininessValue)
{
	materialShader.SetFloat("material.shininess", shininess = _shininessValue);
}

void UMaterial::SetLightSourcePosition(FVector _lightSourcePosition)
{
	lightSourcePosition = _lightSourcePosition;
	materialShader.SetVec3("light.position", lightSourcePosition);
	materialShader.SetVec3("lightPos", lightSourcePosition);
}

void UMaterial::SetCameraPosition(FVector _cameraPosition)
{
	cameraPosition = _cameraPosition;
	materialShader.SetVec3("viewPos", cameraPosition);
}

void UMaterial::SetMVPMatrix(FMatrix _currentModel, FMatrix _currentView, FMatrix _currentProjection)
{
	SetCurrentModel(_currentModel);
	SetCurrentProjection(_currentProjection);
	SetCurrentView(_currentView);
}

void UMaterial::SetCurrentProjection(FMatrix _currentProjection)
{
	currentProjection = _currentProjection;
	materialShader.SetMat4("projection", currentProjection);
}

void UMaterial::SetCurrentView(FMatrix _currentView)
{
	currentView = _currentView;
	materialShader.SetMat4("view", currentView);
}

void UMaterial::SetCurrentModel(FMatrix _currentModel)
{
	currentModel = _currentModel;
	materialShader.SetMat4("model", currentModel);
}

void UMaterial::SetCurrentCurrentTime(float _currentTime)
{
	materialShader.SetFloat("time", _currentTime);
}

#pragma endregion