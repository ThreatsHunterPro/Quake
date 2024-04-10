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
	// Vertex
	GLuint vertexArrayID; //
	FTransform* transform;

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

	// Model
	vector<FVector> vertices;
	vector<FVector2> uvs;
	vector<FVector> normals;

	// VBO
	vector<GLuint> indices; //
	vector<FVector> indexed_vertices;
	vector<FVector2> indexed_uvs;
	vector<FVector> indexed_normals;

	// Buffers
	GLuint vertexBuffer; //
	GLuint uvBuffer;
	GLuint normalBuffer;
	GLuint elementBuffer; //

	//Mat
	UMaterial* material;

public:
	UStaticMeshComponent(AActor* _owner);
	~UStaticMeshComponent() override;

	void Start() override;
	void Update(float _deltaTime) override;
	void Stop() override;

	void Init(const FString& _objPath, const FString& _texturePath, bool _useCustomMethod = false);

#pragma region TransformMethods

#pragma region AddMethods

	void AddMeshLocation(const FVector& _location);
	void AddMeshRotation(float _angle, const FVector& _rotation);
	void AddMeshScale(const FVector& _scale);

#pragma endregion

#pragma region SetMethods

	void SetMeshLocation(const FVector& _location);
	void SetMeshLocationAndRotation(const FVector& _location, const FRotator& _rotation);
	void SetMeshRotation(const FRotator& _rotation);
	void SetMeshScale(const FVector& _scale);

#pragma endregion

#pragma region GetMethods

    const FMatrix& GetModelMatrix() const;
	FORCEINLINE FVector GetForward() const { return FVector(-modelMatrix.ToMat4()[2][0], -modelMatrix.ToMat4()[2][1], -modelMatrix.ToMat4()[2][2]); }
	FORCEINLINE FVector GetRight() const { return FVector(modelMatrix.ToMat4()[0][0], modelMatrix.ToMat4()[0][1], modelMatrix.ToMat4()[0][2]); }
	FORCEINLINE FVector GetUp() const { return FVector(modelMatrix.ToMat4()[1][0], modelMatrix.ToMat4()[1][1], modelMatrix.ToMat4()[1][2]); }
	FORCEINLINE FVector GetMeshPosition() const { return FVector(modelMatrix.ToMat4()[3][0], modelMatrix.ToMat4()[3][1], modelMatrix.ToMat4()[3][2]); }
	FORCEINLINE FRotator GetMeshRotation() const { return FRotator(modelMatrix.ToMat4()[0][3], modelMatrix.ToMat4()[1][3], modelMatrix.ToMat4()[2][3]); }
	FORCEINLINE FVector GetMeshScale() const { return FVector(modelMatrix.ToMat4()[0][0], modelMatrix.ToMat4()[1][1], modelMatrix.ToMat4()[2][2]); }

#pragma endregion 

#pragma endregion

private:

#pragma region InitMethods

	void InitVertex();
	void InitShaders();
	void InitMatrix();
	void InitTextures(const FString& _texturePath, bool _useCustomMethod = true);
	void LoadModel(const FString& _objPath);
	void InitBuffers();
	void InitLights();

#pragma endregion

#pragma region UpdateMethods

	void ComputeMVPMatrix();
	void ComputeShader() const;
	void BindTextures() const;
	void ComputeMatrix();
	void ComputeVertices() const;
	void DrawArrays() const;
	void StopRender() const;

#pragma endregion

// OLD STATIC MESH
//	void InitCreation(const TArray<float>& _vertices, const TArray<float>& _indices);
//	void InitCreationByType(const PrimitiveType& _type);
//	void DrawElement();
//private:
//	void InitArrayAndBuffers();
//	void SetArrayAndBuffers();
//	void InitMaterial();
};
