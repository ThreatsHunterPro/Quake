#pragma once 
#include "../Components/UComponent.h"
#include "../UObject.h"
#include "../../Core/Math/FRotator.h"
#include "../../Core/Math/FVector/TVector.h"
#include "../../Core/Math/FMatrix.h"

class UMaterial;
class UPrimitiveMesh;
class CustomShader;
class AActor;
enum PrimitiveType;


class UStaticMeshComponent : public UComponent
{
	TArray<FVector> vertices;
	TArray<float> indices;

	// Shader
	GLuint programID;
	FString vertexShaderPath;
	FString fragmentShaderPath;

	// Matrix
	GLuint matrixID;
	FMatrix modelMatrix;
	GLuint modelMatrixID;
	FMatrix viewMatrix;
	GLuint viewMatrixID;
	FMatrix projectionMatrix;

	//Objects
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	//Mat
	UMaterial* material;

public:
	UStaticMeshComponent(AActor* _owner);
	//UStaticMeshComponent(UPrimitiveMesh* _primitive = nullptr);
	~UStaticMeshComponent() override;
	inline const TArray<FVector>& GetVertices() const { return vertices; }
	inline const TArray<float>& GetIndices() const { return indices; }

	const FMatrix& GetModelMatrix() const; 
	const FVector& GetForward() const ;
	const FVector& GetRight() const ;
	const FVector& GetUp() const ;
	const FVector& GetMeshPosition() const; 
	const FRotator& GetMeshRotation() const; 
	const FVector& GetMeshScale() const; 

public:

	void Start() override;
	void Update(float _deltaTime) override;
	void Stop() override;
	void Init(const FString& _objPath, const FString& _texturePath, bool _useCustomMethod = false);


	// ADD
	void AddMeshLocation(const FVector& _location);
	void AddMeshRotation(float _angle, const FVector& _rotation);
	void AddMeshScale(const FVector& _scale);

	//SET
	void SetMeshLocation(const FVector& _location);
	void SetMeshLocationAndRotation(const FVector& _location, const FRotator& _rotation);
	void SetMeshRotation(const FRotator& _rotation);
	void SetMeshScale(const FVector& _scale);

#pragma region InitMethods
	void InitVertex();
	void InitShaders();
	void InitMatrix();
	void InitTextures(const FString& _texturePath, bool _useCustomMethod = true);
	void LoadModel(const FString& _objPath);
	void InitBuffers();
	void InitLights();
#pragma endregion InitMethods

#pragma region UpdateMethods
	void ComputeMVPMatrix();
	void ComputeShader() const;
	void BindTextures() const;
	void ComputeMatrix();
	void ComputeVertices() const;
	void DrawArrays() const;
	void StopRender() const;
#pragma endregion

	void InitCreation(const TArray<float>& _vertices, const TArray<float>& _indices);
	void InitCreationByType(const PrimitiveType& _type);
	void DrawElement();
private:
	void InitArrayAndBuffers();
	void SetArrayAndBuffers();
	void InitMaterial();
};
