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
	static vector<float> GetFloatArrayByType(const PrimitiveType& _type);
};