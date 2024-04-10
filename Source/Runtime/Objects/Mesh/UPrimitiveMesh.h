#pragma once
#include "../../../CoreMinimal.h"

enum PrimitiveType
{
	PT_BOX,
	PT_SPHERE,
	PT_PLANE,
	PT_CYLINDER,
	PT_CONE,

	PT_COUNT
};


class UPrimitiveMesh
{
public:
	static void GetFloatArrayByType(const PrimitiveType& _type, TArray<float>& _vertices,TArray<float>& _indices);
private:
	static void GenerateSphereVerticesAndIndices(TArray<float>& _vertices, TArray<float>& _indices);
	static void GenerateBoxVertices(TArray<float>& _vertices);
};