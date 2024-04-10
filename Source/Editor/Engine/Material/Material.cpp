#include "Material.h"



#define STB_IMAGE_IMPLEMENTATION

#pragma region Constructor

UMaterial::UMaterial()
{
}

UMaterial::UMaterial(const char* _vertexPath, const char* _fragmentPath)
{
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
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularTexture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, emissionTexture);
}

void UMaterial::SetLightValues(FVector _ambientValue, FVector _diffuseValue, FVector _specularValue)
{
	SetAmbientValue(_ambientValue);
	SetDiffuseValue(_diffuseValue);
	SetSpecularValue(_specularValue);
}

void UMaterial::Use()
{
	materialShader.Use();
}

void UMaterial::LoadMaterialShader(const char* _vertexPath, const char* _fragmentPath)
{
	materialShader.LoadShadersFromPath(_vertexPath, _fragmentPath);
}

void UMaterial::LoadDiffuseTexture(const char* _texturePath, int _wrapParam, int _filterParam)
{
	diffuseTexture = LoadTexture(_texturePath, _wrapParam, _filterParam);
}

void UMaterial::LoadSpecularTexture(const char* _texturePath, int _wrapParam, int _filterParam)
{
	specularTexture = LoadTexture(_texturePath, _wrapParam, _filterParam);
}

void UMaterial::LoadEmissionTexture(const char* _texturePath, int _wrapParam, int _filterParam)
{
	emissionTexture = LoadTexture(_texturePath, _wrapParam, _filterParam);
}

unsigned int UMaterial::LoadTexture(const char* _path, int _wrapParam, int _filterParam)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(_path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterParam);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << _path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

#pragma endregion

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
	shininess = _shininessValue;
	materialShader.SetFloat("material.shininess", shininess);
}

void UMaterial::SetLightSourcePosition(FVector _lightSourcePosition)
{
	lightSourcePosition = _lightSourcePosition;
	materialShader.SetVec3("light.position", lightSourcePosition);
}

void UMaterial::SetLightDirection(FVector _direction)
{
	cameraDirection = _direction;
	materialShader.SetVec3("light.direction", cameraDirection);
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