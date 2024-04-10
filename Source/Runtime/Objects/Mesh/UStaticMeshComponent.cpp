#include "UStaticMeshComponent.h"
#include "../../Managers/TimerManager.h"
#include "../../../Editor/Engine/Material/Material.h"
#include "../../Managers/CameraManager.h"
#include "UPrimitiveMesh.h"
//#include "../../../Editor/Engine/Texture/CustomTexture.h"

UStaticMeshComponent::UStaticMeshComponent(AActor* _owner) : UComponent(_owner)
{
	VAO = GLuint();

	// Shader
	programID = GLuint();
	vertexShaderPath = "StandardShading.vertexshader";
	fragmentShaderPath = "StandardShading.fragmentshader";

	// Matrix
	matrixID = GLuint();
	modelMatrix = FMatrix::Identity;
	modelMatrixID = GLuint();
	viewMatrix = FMatrix::Identity;
	viewMatrixID = GLuint();
	projectionMatrix = FMatrix::Identity;

	// Model
	vertices = TArray<FVector>();

	// VBO
	//indices = vector<unsigned short>();
	//indexed_vertices = vector<vec3>();
	//indexed_uvs = vector<vec2>();
	//indexed_normals = vector<vec3>();

	//// Buffers
	//vertexBuffer = GLuint();
	//uvBuffer = GLuint();
	//normalBuffer = GLuint();
	//elementBuffer = GLuint();

	//// Lights
	//lightID = GLuint();
}

//UStaticMeshComponent::UStaticMeshComponent(UPrimitiveMesh* _primitive)
//{
//	//vertices = TArray<float>();
//	//indices = TArray<float>();
//	//VAO = GLuint();
//	//VBO = GLuint();
//	//EBO = GLuint();
//	//material = new UMaterial();
//}

UStaticMeshComponent::~UStaticMeshComponent()
{
	//TODO Remove
	delete material;
}

const FMatrix& UStaticMeshComponent::GetModelMatrix() const 
{
	return modelMatrix;
}

const FVector& UStaticMeshComponent::GetForward() const
{
	const FVector& _vec = FVector(-modelMatrix.ToMat4()[2][0], -modelMatrix.ToMat4()[2][1], -modelMatrix.ToMat4()[2][2]);
	return _vec;
}

const FVector& UStaticMeshComponent::GetRight() const
{
	const FVector& _vec = FVector(modelMatrix.ToMat4()[0][0], modelMatrix.ToMat4()[0][1], modelMatrix.ToMat4()[0][2]);
	return _vec;
}

const FVector& UStaticMeshComponent::GetUp() const
{
	const FVector& _vec = FVector(modelMatrix.ToMat4()[1][0], modelMatrix.ToMat4()[1][1], modelMatrix.ToMat4()[1][2]);
	return _vec;
}

const FVector& UStaticMeshComponent::GetMeshPosition() const
{
	const FVector& _vec = FVector(modelMatrix.ToMat4()[3][0], modelMatrix.ToMat4()[3][1], modelMatrix.ToMat4()[3][2]);
	return _vec;
}

const FRotator& UStaticMeshComponent::GetMeshRotation() const
{
	const FRotator& _rot = FRotator(modelMatrix.ToMat4()[0][3], modelMatrix.ToMat4()[1][3], modelMatrix.ToMat4()[2][3]);
	return _rot;
}

const FVector& UStaticMeshComponent::GetMeshScale() const
{
	const FVector& _vec = FVector(modelMatrix.ToMat4()[0][0], modelMatrix.ToMat4()[1][1], modelMatrix.ToMat4()[2][2]);
	return _vec;
}

void UStaticMeshComponent::InitCreation(const TArray<float>& _vertices, const TArray<float>& _indices)
{
	material->LoadMaterialShader("Element.vs", "Element.fs");
	/*matrixID = glGetUniformLocation(programID, "MVP");
	viewMatrixID = glGetUniformLocation(programID, "M");
	modelMatrixID = glGetUniformLocation(programID, "V");*/
	InitArrayAndBuffers();
	/*vertices = _vertices;
	indices = _indices;*/
	SetArrayAndBuffers();
}

void UStaticMeshComponent::InitCreationByType(const PrimitiveType& _type)
{
	InitArrayAndBuffers();
	//UPrimitiveMesh::GetFloatArrayByType(_type, vertices, indices);
	SetArrayAndBuffers();
}

void UStaticMeshComponent::InitArrayAndBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void UStaticMeshComponent::SetArrayAndBuffers()
{
	glBufferData(GL_ARRAY_BUFFER, vertices.Num() * sizeof(float), vertices.GetArray(), GL_STATIC_DRAW);

	if (!indices.IsEmpty())
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.Num() * sizeof(float), indices.GetArray(), GL_STATIC_DRAW);
	}

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// color attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// texture coord attribute
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// light
	//glGenVertexArrays(1, &lightVAO);
	//glBindVertexArray(lightVAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	if (!indices.IsEmpty())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	InitMaterial();
}

void UStaticMeshComponent::InitMaterial()
{
	material->LoadDiffuseTexture("../Content/Textures/WoodenBox.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	material->LoadSpecularTexture("../Content/Textures/WoodenBox_Specular.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	material->LoadEmissionTexture("../Content/Textures/matrix.jpg", GL_REPEAT, GL_LINEAR);
	material->InitMaterialTextures();
}

void UStaticMeshComponent::DrawElement()
{
	material->Use();
	CameraManager& _camera = CameraManager::GetInstance();
	material->SetLightSourcePosition(_camera.GetPosition());
	material->SetLightDirection(_camera.GetForward());

	material->SetAmbientValue(FVector(0.1f, 0.1f, 0.1f));
	material->SetDiffuseValue(FVector(0.8f, 0.8f, 0.8f));
	material->SetSpecularValue(FVector(1.0f, 1.0f, 1.0f));

	material->BindAndUseMaterialTextures();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 54);

	FMatrix _model = FMatrix::Identity;
	//_model = translate(_model, FVector(0.0f, 0.0f, -5.0f));
	_model = rotate(_model.ToMat4(), TimerManager::GetInstance().DeltaTimeSeconds(), vec3(0.0f, 1.0f, 0.0f));
	material->SetCurrentModel(_model);
}

void UStaticMeshComponent::Start()
{
}

void UStaticMeshComponent::Update(float _deltaTime)
{
}

void UStaticMeshComponent::Stop()
{
}

void UStaticMeshComponent::Init(const FString& _objPath, const FString& _texturePath, bool _useCustomMethod)
{
}

void UStaticMeshComponent::AddMeshLocation(const FVector& _location)
{
}

void UStaticMeshComponent::AddMeshRotation(float _angle, const FVector& _rotation)
{
}

void UStaticMeshComponent::AddMeshScale(const FVector& _scale)
{
}

void UStaticMeshComponent::SetMeshLocation(const FVector& _location)
{
}

void UStaticMeshComponent::SetMeshLocationAndRotation(const FVector& _location, const FRotator& _rotation)
{
}

void UStaticMeshComponent::SetMeshRotation(const FRotator& _rotation)
{
}

void UStaticMeshComponent::SetMeshScale(const FVector& _scale)
{
}

void UStaticMeshComponent::InitVertex()
{
}

void UStaticMeshComponent::InitShaders()
{
}

void UStaticMeshComponent::InitMatrix()
{
}

void UStaticMeshComponent::InitTextures(const FString& _texturePath, bool _useCustomMethod)
{
}

void UStaticMeshComponent::LoadModel(const FString& _objPath)
{
}

void UStaticMeshComponent::InitBuffers()
{
}

void UStaticMeshComponent::InitLights()
{
}

void UStaticMeshComponent::ComputeMVPMatrix()
{
}

void UStaticMeshComponent::ComputeShader() const
{
}

void UStaticMeshComponent::BindTextures() const
{
}

void UStaticMeshComponent::ComputeMatrix()
{
}

void UStaticMeshComponent::ComputeVertices() const
{
}

void UStaticMeshComponent::DrawArrays() const
{
}

void UStaticMeshComponent::StopRender() const
{
}
