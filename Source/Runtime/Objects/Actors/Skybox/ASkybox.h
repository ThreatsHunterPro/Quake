#pragma once
#include "../../../../Editor/Engine/Shader/CustomShader.h"
#include "../AActor.h"
#include <Source/Runtime/Managers/CameraManager.h>
class ASkybox : public AActor
{
	CustomShader skyboxShader = CustomShader();
	GLuint skyboxTexture = 0;
	GLuint skyboxVAO = 0;
	GLuint skyboxVBO = 0;
	GLuint skyboxEBO = 0;
	vector<string> skyboxFacesPath ={
		"../Content/Textures/Skybox/right.jpg",
		"../Content/Textures/Skybox/left.jpg",
		"../Content/Textures/Skybox/top.jpg",
		"../Content/Textures/Skybox/bottom.jpg",
		"../Content/Textures/Skybox/front.jpg",
		"../Content/Textures/Skybox/back.jpg",
	};
	FMatrix view = FMatrix::Identity;
	FMatrix projection = FMatrix::Identity;

public:
	ASkybox() = default; 
	void BeginPlay();
	void Update(CameraManager _camera);

	GLuint LoadCubeMap(vector<string> _allFaces);
	void EndPlay();
};