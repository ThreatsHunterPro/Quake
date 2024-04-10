#pragma once
#include "../Shader/CustomShader.h"
#include "../../../Runtime/Core/Math/FMatrix.h"
#include "../../../Runtime/Core/Math/FVector/TVector.h"
#include "../Texture/CustomTexture.h"

class UMaterial
{
	CustomShader materialShader;

	CustomTexture diffuseTexture;
	CustomTexture specularTexture;
	CustomTexture emissionTexture;

	float shininess;
	
	FVector lightSourcePosition;
	FVector cameraPosition;

	FVector ambientValue;
	FVector diffuseValue;
	FVector specularValue;

	FMatrix currentProjection;
	FMatrix currentView;
	FMatrix currentModel;


public:
	UMaterial();
	UMaterial(const char* _vertexPath, const char* _fragmentPath);

	FORCEINLINE CustomShader GetMaterialShader() const { return materialShader; }

	FORCEINLINE CustomTexture GetDiffuseTexture() const { return diffuseTexture; }
	FORCEINLINE CustomTexture GetSpecularTexture() const { return specularTexture; }
	FORCEINLINE CustomTexture GetEmissionTexture() const { return emissionTexture; }

	FORCEINLINE float GetShininess() const { return shininess; }

	FORCEINLINE FVector GetLightSourcePosition() const { return lightSourcePosition; }
	FORCEINLINE FVector GetCameraPosition() const { return cameraPosition; }
	FORCEINLINE FVector GetAmbientValue() const { return ambientValue; }
	FORCEINLINE FVector GetDiffuseValue() const { return diffuseValue; }
	FORCEINLINE FVector GetSpecularValue() const { return specularValue; }

	FORCEINLINE FMatrix GetCurrentProjection() const { return currentProjection; }
	FORCEINLINE FMatrix GetCurrentView() const { return currentView; }
	FORCEINLINE FMatrix GetCurrentModel() const { return currentModel; }

public:
	void LoadMaterialShader(const char* _vertexPath, const char* _fragmentPath);
	void LoadDiffuseTexture(const char* _texturePath, int _wrapParam, int _filterParam);
	void LoadSpecularTexture(const char* _texturePath, int _wrapParam, int _filterParam);
	void LoadEmissionTexture(const char* _texturePath, int _wrapParam, int _filterParam);
	void InitMaterialTextures();
	void BindAndUseMaterialTextures();
	void SetLightValues(FVector _ambientValue, FVector _diffuseValue, FVector _specularValue);
	void SetAmbientValue(FVector _ambientValue);
	void SetDiffuseValue(FVector _diffuseValue);
	void SetSpecularValue(FVector _specularValue);
	void SetShininessValue(float _shininessValue);
	void SetLightSourcePosition(FVector _lightSourcePosition);
	void SetCameraPosition(FVector _cameraPosition);
	void SetMVPMatrix(FMatrix _currentModel, FMatrix _currentView, FMatrix _currentProjection);
	void SetCurrentProjection(FMatrix _currentProjection);
	void SetCurrentView(FMatrix _currentView);
	void SetCurrentModel(FMatrix _currentModel);
	void SetCurrentCurrentTime(float _currentTime);
};

