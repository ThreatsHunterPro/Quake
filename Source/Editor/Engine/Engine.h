#pragma once
#include "Source/CoreMinimal.h"
#include "EngineWindow.h"
#include "..\..\Editor\Engine\Shader\CustomShader.h"
#include "..\..\Runtime\Core\Math\FVector\TVector.h"
#include "..\..\Runtime\Core\Containers\TArray.h"
#include "../../Runtime/Objects/Actors/Lights/PointLight/APointLight.h"

class Engine
{
	float floatSlider = 0.5f;

	int counter = 0;
	EngineWindow* mainWindow;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
	GLuint texture1;
	GLuint texture2;
	CustomShader elementShader;

	bool use2D;
	bool multipleCubes;
	bool rotateElements;

	int cubeIndex;
	FVector cubePositions[10] = {
		FVector(0.0f,  0.0f,  0.0f),
		FVector(2.0f,  5.0f, -15.0f),
		FVector(-1.5f, -2.2f, -2.5f),
		FVector(-3.8f, -2.0f, -12.3f),
		FVector(2.4f, -0.4f, -3.5f),
		FVector(-1.7f,  3.0f, -7.5f),
		FVector(1.3f, -2.0f, -2.5f),
		FVector(1.5f,  2.0f, -2.5f),
		FVector(1.5f,  0.2f, -1.5f),
		FVector(-1.3f,  1.0f, -1.5f)
	};

	bool drawLamp;
	bool moveLamp;
	bool rotateLamp;
	GLuint lightVAO;
	FVector lightPos;
	GLuint diffuseMap;
	GLuint specularMap;
	GLuint emissionMap;
	CustomShader lampShader;

	// Point light
	APointLight pointLight;

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
	void DrawLamp();
	void DrawElement();
	void DrawElements();
	void ChangeElementColor();
#pragma endregion

	void Stop();
	void ClearElements();

public:
	void Launch();
	FVector GetNextCubePosition();
};