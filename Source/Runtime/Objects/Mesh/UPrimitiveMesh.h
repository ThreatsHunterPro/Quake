#pragma once
#include "../../../CoreMinimal.h"

enum PrimitiveType
{
	PT_BOX,
	PT_PLANE,
	PT_SPHERE,
	PT_CYLINDER,
	PT_CONE,

	PT_COUNT
};


class UPrimitiveMesh
{
	PrimitiveType type;
private:
	//static float GenerateBoxVertexesFloat();
	//static float GenerateSphereVertexesFloat();
	//static float GeneratePlaneVertexesFloat();
	//static float GenerateCylinderVertexesFloat();
	//static float GenerateConeVertexesFloat();

public:
	static const float* GetFloatArrayByType(const PrimitiveType& _type);
};