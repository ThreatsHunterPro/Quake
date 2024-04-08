#include "UStaticMesh.h"
#include "../../Managers/TimerManager.h"
#include "../../../Editor/Engine/Material/Material.h"
//#include "../../../Editor/Engine/Texture/CustomTexture.h"

UStaticMesh::UStaticMesh()
{
	primitiveType = PT_NONE;
	//text = nullptr;
	VAO = 0;
	VBO = 0;
	material = nullptr;
}

UStaticMesh::UStaticMesh(const PrimitiveType& _type/*, CustomTexture* _texture*/)
{
	primitiveType = _type;
	//text = _texture;
	VAO = 0;
	VBO = 0;
	material = nullptr;
}

UStaticMesh::~UStaticMesh()
{
	//TODO Remove
	delete material;
}

void UStaticMesh::Generate()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	const function<void()> _callback[] = {
		[this]() { GenerateBox(); },
		[this]() { /*GeneratePlane()*/; },
		[this]() { /*GenerateSphere()*/; },
		[this]() { /*GenerateCylinder()*/; },
		[this]() { /*GenerateCone()*/; },
	};

	_callback[primitiveType]();
}

void UStaticMesh::GenerateBox()
{
	const float _vertices[] = {
		// position				// normals				// color			// texture
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f, 0.0f,  	0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, -1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,		0.0f, 0.0f, 1.0f,	0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,		1.0f,  0.0f,  0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,		1.0f,  0.0f,  0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, -1.0f,  0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,		0.0f, 0.0f, 1.0f,	0.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

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

	//text->LoadTexture();
}

void UStaticMesh::DrawElement()
{
	//ApplyShader();

	mat4 _model = mat4(1.0f);
	//_model = translate(_model, vec3(0.0f, 0.0f, -5.0f));
	_model = rotate(_model, TimerManager::GetInstance().DeltaTimeSeconds(), vec3(0.0f, 1.0f, 0.0f));
	//elementShader.SetMat4("model", _model);
}








