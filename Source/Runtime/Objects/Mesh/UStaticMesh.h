#pragma once 
#include "../../../CoreMinimal.h"
#include "../UObject.h"
//#include "../../../Editor/Engine/Material/Material.h"

//class CustomTexture;
class Material;

enum PrimitiveType
{
	PT_NONE,

	PT_BOX,
	PT_PLANE,
	PT_SPHERE,
	PT_CYLINDER,
	PT_CONE,

	PT_COUNT
};

class UStaticMesh : public UObject
{
	PrimitiveType primitiveType;

	//TSmartPtr<CustomTexture> texture;
	//Texture
	//CustomTexture* text;
	
	//Vertex Array Object
	GLuint VAO;
	//Vertex Buffer Object
	GLuint VBO;

	//Material
	Material* material;

	//Shader
	//CustomShader lampShader;
public:
	FORCEINLINE const PrimitiveType& GetPrimitiveType() const { return primitiveType; }
	//FORCEINLINE const TSmartPtr<CustomTexture>& GetTexture() const { return texture; }
	//FORCEINLINE CustomTexture* GetTexture() const { return text; }
public:
	UStaticMesh();
	UStaticMesh(const PrimitiveType& _type);
	//UStaticMesh(const PrimitiveType& _type/*, CustomTexture* _texture = nullptr*/);
	~UStaticMesh();
public:
	void Generate();
private:
	void GenerateBox();
	void DrawElement();

};
