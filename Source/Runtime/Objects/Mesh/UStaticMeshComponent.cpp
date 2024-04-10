#include "UStaticMeshComponent.h"
#include "../../Managers/TimerManager.h"
#include "../../../Editor/Engine/Material/Material.h"
#include "../../Managers/CameraManager.h"
#include "../Camera/UCamera.h"
#include "UPrimitiveMesh.h"
#include "../../Core/Math/FMatrix.h"

//#include "../../../Editor/Engine/Texture/CustomTexture.h"

UStaticMeshComponent::UStaticMeshComponent(AActor* _owner) : UComponent(_owner)
{
	vertexArrayID = GLuint();

	// Shader
	programID = GLuint();
	vertexShaderPath = VERTEX_SHADER_PATH;
	fragmentShaderPath = FRAGMENT_SHADER_PATH;

	// Matrix
	matrixID = GLuint();
	modelMatrix = FMatrix();
	modelMatrixID = GLuint();
	viewMatrix = FMatrix();
	viewMatrixID = GLuint();
	projectionMatrix = FMatrix();

	// Model
	vertices = vector<FVector>();
	uvs = vector<FVector2>();
	normals = vector<FVector>();

	// VBO
	indices = vector<GLuint>();
	indexed_vertices = vector<FVector>();
	indexed_uvs = vector<FVector2>();
	indexed_normals = vector<FVector>();

	// Buffers
	vertexBuffer = GLuint();
	uvBuffer = GLuint();
	normalBuffer = GLuint();
	elementBuffer = GLuint();
}

//UUStaticMeshComponent::UUStaticMeshComponent(UPrimitiveMesh* _primitive)
//{
//	//vertices = TArray<float>();
//	//indices = TArray<float>();
//	//VAO = GLuint();
//	//VBO = GLuint();
//	//EBO = GLuint();
//	//material = new UMaterial();
//}

UStaticMeshComponent::~UStaticMeshComponent() = default;

void UStaticMeshComponent::Start()
{
	BASE::Start();
}
void UStaticMeshComponent::Update(float _deltaTime)
{
	BASE::Update(_deltaTime);

	/*
	// Display the mesh only if owner is into camera's frustum
	UShapeComponent* _shapeComponent = owner->GetComponent<UShapeComponent>();
	if (_shapeComponent && _shapeComponent->IsOnFrustum(Game::GameCamera()->GetFrustum(), owner) || !_shapeComponent)
	{
		ComputeMVPMatrix();
		ComputeShader();
		BindTextures();
		ComputeMatrix();
		ComputeVertices();
		DrawArrays();
	}*/

	// Get le MVP du static mesh
	ComputeMVPMatrix();
	//
	ComputeShader();
	BindTextures();
	ComputeMatrix();
	ComputeVertices();
	DrawArrays();
	StopRender();
}
void UStaticMeshComponent::Stop()
{
	BASE::Stop();

	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteProgram(programID);
	//glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &vertexArrayID);
}

#pragma region TransformMethods

#pragma region AddMethods

void UStaticMeshComponent::AddMeshLocation(const FVector& _location)
{
	//modelMatrix = modelMatrix.Scaletranslation(FVector(_location.X, _location.Y, _location.Z));
}
void UStaticMeshComponent::AddMeshRotation(const float _angle, const FVector& _axis)
{
	//modelMatrix = rotate(modelMatrix, radians(_angle), vec3(_axis.X, _axis.Y, _axis.Z));
}
void UStaticMeshComponent::AddMeshScale(const FVector& _scale)
{
	//modelMatrix = scale(modelMatrix, vec3(_scale.X, _scale.Y, _scale.Z));
}

#pragma endregion

#pragma region SetMethods

void UStaticMeshComponent::SetMeshLocation(const FVector& _location)
{
	modelMatrix.ToMat4()[3][0] = _location.X;
	modelMatrix.ToMat4()[3][1] = _location.Y;
	modelMatrix.ToMat4()[3][2] = _location.Z;
}
void UStaticMeshComponent::SetMeshLocationAndRotation(const FVector& _location, const FRotator& _rotation)
{
	SetMeshLocation(_location);
	SetMeshRotation(_rotation);
}
void UStaticMeshComponent::SetMeshRotation(const FRotator& _rotation)
{
	modelMatrix.ToMat4()[0][3] = _rotation.Pitch;
	modelMatrix.ToMat4()[1][3] = _rotation.Roll;
	modelMatrix.ToMat4()[2][3] = _rotation.Yaw;
}
void UStaticMeshComponent::SetMeshScale(const FVector& _scale)
{
	modelMatrix.ToMat4()[0][0] = _scale.X;
	modelMatrix.ToMat4()[1][1] = _scale.Y;
	modelMatrix.ToMat4()[2][2] = _scale.Z;
}

const FMatrix& UStaticMeshComponent::GetModelMatrix() const
{
	return modelMatrix;
}


#pragma endregion

#pragma endregion

#pragma region InitMethods

void UStaticMeshComponent::Init(const FString& _objPath, const FString& _texturePath, bool _useCustomMethod)
{
	if (_texturePath.IsEmpty() || _objPath.IsEmpty()) return;

	InitVertex();
	InitShaders();
	InitMatrix();
	InitTextures(_texturePath, _useCustomMethod);
	LoadModel(_objPath);
	InitBuffers();
	InitLights();
}
void UStaticMeshComponent::InitVertex()
{
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
}
void UStaticMeshComponent::InitShaders()
{
	programID = LoadShaders(vertexShaderPath.ToCstr(),fragmentShaderPath.ToCstr());
}
void UStaticMeshComponent::InitMatrix()
{
	matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "M");
	modelMatrixID = glGetUniformLocation(programID, "V");
}
void UStaticMeshComponent::InitTextures(const FString& _texturePath, bool _useCustomMethod)
{
	char _fullTexturePath[100 * sizeof(char)];
	string _str = _texturePath.GetText();
	strcpy_s(_fullTexturePath, _str.c_str());

	if (!_useCustomMethod)
	{
		//strcat_s(_fullTexturePath, sizeof(_fullTexturePath), ".DDS");
		//texture = loadDDS(_fullTexturePath);
	}

	else
	{
		//strcat_s(_fullTexturePath, sizeof(_fullTexturePath), ".bmp");
		//texture = loadBMP_custom(_fullTexturePath);
	}

	//textureID = glGetUniformLocation(programID, "myTextureSampler");
}
void UStaticMeshComponent::LoadModel(const FString& _objPath)
{
	vector<vec2> _uvs;
	vector<vec3> _normals;
	//bool _res = loadOBJ(_path + _objPath, vertices, _uvs, _normals);
	//indexVBO(vertices, _uvs, _normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
}
void UStaticMeshComponent::InitBuffers()
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(vec3), &indexed_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(vec2), &indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(vec3), &indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &elementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}
void UStaticMeshComponent::InitLights()
{
	//glUseProgram(programID);
	//lightID = glGetUniformLocation(programID, "LightPosition_worldspace");
}

#pragma endregion

#pragma region UpdateMethods

void UStaticMeshComponent::ComputeMVPMatrix()
{
	projectionMatrix = CameraManager::GetInstance().GetCameras()[0]->GetProjectionMatrix();
	viewMatrix = CameraManager::GetInstance().GetCameras()[0]->GetViewMatrix();
}
void UStaticMeshComponent::ComputeShader() const
{
	glUseProgram(programID);
	const vec3 _lightPos = vec3(4, 4, 4);
	//glUniform3f(lightID, _lightPos.x, _lightPos.y, _lightPos.z);
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, &viewMatrix.ToMat4()[0][0]);
}
void UStaticMeshComponent::BindTextures() const
{
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glUniform1i(textureID, 0);
}
void UStaticMeshComponent::ComputeMatrix()
{
	FMatrix _mvp = projectionMatrix * viewMatrix * modelMatrix;
	glUniformMatrix4fv(matrixID, 1, GL_FALSE, &_mvp.ToMat4()[0][0]);
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &modelMatrix.ToMat4()[0][0]);
}
void UStaticMeshComponent::ComputeVertices() const
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
}
void UStaticMeshComponent::DrawArrays() const
{
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_SHORT, nullptr);
}
void UStaticMeshComponent::StopRender() const
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

#pragma region OLD STATIC MESH
//void UUStaticMeshComponent::InitCreation(const TArray<float>& _vertices, const TArray<float>& _indices)
//{
//	material->LoadMaterialShader("Element.vs", "Element.fs");
//	/*matrixID = glGetUniformLocation(programID, "MVP");
//	viewMatrixID = glGetUniformLocation(programID, "M");
//	modelMatrixID = glGetUniformLocation(programID, "V");*/
//	InitArrayAndBuffers();
//	/*vertices = _vertices;
//	indices = _indices;*/
//	SetArrayAndBuffers();
//}
//
//void UUStaticMeshComponent::InitCreationByType(const PrimitiveType& _type)
//{
//	InitArrayAndBuffers();
//	//UPrimitiveMesh::GetFloatArrayByType(_type, vertices, indices);
//	SetArrayAndBuffers();
//}
//
//void UUStaticMeshComponent::InitArrayAndBuffers()
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//}
//
//void UUStaticMeshComponent::SetArrayAndBuffers()
//{
//	glBufferData(GL_ARRAY_BUFFER, vertices.Num() * sizeof(float), vertices.GetArray(), GL_STATIC_DRAW);
//
//	if (!indices.IsEmpty())
//	{
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.Num() * sizeof(float), indices.GetArray(), GL_STATIC_DRAW);
//	}
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// normals
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	// color attribute
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//
//	// texture coord attribute
//	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
//	glEnableVertexAttribArray(3);
//
//	// light
//	//glGenVertexArrays(1, &lightVAO);
//	//glBindVertexArray(lightVAO);
//
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	if (!indices.IsEmpty())
//	{
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	}
//
//	InitMaterial();
//}
//
//void UUStaticMeshComponent::InitMaterial()
//{
//	material->LoadDiffuseTexture("../Content/Textures/WoodenBox.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
//	material->LoadSpecularTexture("../Content/Textures/WoodenBox_Specular.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
//	material->LoadEmissionTexture("../Content/Textures/matrix.jpg", GL_REPEAT, GL_LINEAR);
//	material->InitMaterialTextures();
//}
//
//void UUStaticMeshComponent::DrawElement()
//{
//	//material->Use();
//	/*CameraManager& _camera = CameraManager::GetInstance();
//	material->SetLightSourcePosition(_camera.GetPosition());
//	material->SetLightDirection(_camera.GetForward());*/
//
//	material->SetAmbientValue(FVector(0.1f, 0.1f, 0.1f));
//	material->SetDiffuseValue(FVector(0.8f, 0.8f, 0.8f));
//	material->SetSpecularValue(FVector(1.0f, 1.0f, 1.0f));
//
//	material->BindAndUseMaterialTextures();
//
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, 54);
//
//	FMatrix _model = FMatrix::Identity;
//	//_model = translate(_model, FVector(0.0f, 0.0f, -5.0f));
//	_model = rotate(_model.ToMat4(), TimerManager::GetInstance().DeltaTimeSeconds(), vec3(0.0f, 1.0f, 0.0f));
//	material->SetCurrentModel(_model);
//}
#pragma endregion OLD STATIC MESH