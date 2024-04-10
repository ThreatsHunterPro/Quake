#pragma once
#include "Source/CoreMinimal.h"
#include "EngineWindow.h"
#include "..\..\Editor\Engine\Shader\CustomShader.h"
#include "..\..\Runtime\Core\Math\FVector\TVector.h"
#include "..\..\Runtime\Core\Containers\TArray.h"
#include "../../Runtime/Objects/Actors/Lights/PointLight/APointLight.h"
#include "../../Runtime/Objects/Actors/Lights/SpotLight/ASpotLight.h"
#include "../../Runtime/Objects/Actors/Lights/DirectionalLight/ADirectionalLight.h"	

class Engine
{
	EngineWindow* mainWindow;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint texture1;
	GLuint texture2;
	CustomShader* elementShader;

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	GLuint quadVAO;
	GLuint quadVBO;
	GLuint shadowFBO;
	GLuint shadowMap;
	FMatrix lightSpaceMatrix;
	CustomShader* shadowShader;
	CustomShader* debugShader;
	float near_plane, far_plane;

	bool use2D;
	bool multipleCubes;
	bool rotateElements;

	int cubeIndex;
	FVector cubePositions[5] = {
		FVector(3.0f, 0.0f,  0.0f),
		FVector(1.5f, 0.0f, -1.5f),
		FVector(1.5f, 0.0f, 1.5f),
		FVector(-1.5f, 0.0f, 0.0f),
		FVector(1.5f, 0.0f, 0.0f)
	};

	bool drawLamp;
	bool moveLamp;
	bool rotateLamp;
	GLuint lightVAO;
	FVector lightPos;
	GLuint diffuseMap;
	GLuint specularMap;
	GLuint emissionMap;
	CustomShader* lampShader;

	// Point light
	ADirectionalLight* directionalLight;
	APointLight* pointLight;
	ASpotLight* spotLight;

public:
	FORCEINLINE static Engine& GetInstance()
	{
		static Engine _instance;
		return _instance;
	}

public:
	Engine();
	~Engine();

private:
	void Start();
	GLuint LoadTexture(const char* _path, const int _wrapParam, const int _filterParam);
	void Update();
	void ChangeBgColor();

#pragma region Draws
	void Draw();
	void ApplyShader();
	void ApplyShadow();
	void RenderScene(CustomShader* _shader);
	void DrawLamp();
	void DrawElement(CustomShader* _shader);
	void DrawElements(CustomShader* _shader);
	void ChangeElementColor();
#pragma endregion

	void Stop();
	void ClearElements();

public:
	void Launch();
	FVector GetNextCubePosition();
};