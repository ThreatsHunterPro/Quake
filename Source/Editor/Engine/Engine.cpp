#include "Engine.h"
#include "..\..\Runtime\Managers\InputManager.h"
#include "..\..\Runtime\Managers\CameraManager.h"
#include "..\..\Runtime\Managers\TimerManager.h"
#include "../../Runtime/Objects/Camera/UCamera.h"


Engine::Engine()
{
	mainWindow = new EngineWindow();

	mainCamera = new UCamera();
	skybox = new ASkybox();

	VAO = GLuint();
	VBO = GLuint();
	EBO = GLuint();
	texture1 = GLuint();
	texture2 = GLuint();

	use2D = false;
	rotateElements = false;
	multipleCubes = true;

	cubeIndex = 0;

	// Lamp
	drawLamp = true;
	moveLamp = true;
	rotateLamp = false;
	lightVAO = GLuint();
	lightPos = FVector(0.5f, 0.5f, 1.0f);
	lampShader = CustomShader();


	// Material
	woodenBoxMaterial = UMaterial();
}

Engine::~Engine()
{
	delete mainWindow;
	delete mainCamera;
	delete skybox;
}


void Engine::Start()
{

	mainWindow->Start();
	skybox->BeginPlay();
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(mainWindow->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Shaders
	woodenBoxMaterial.LoadMaterialShader("Element.vs", "Element.fs");
	lampShader.LoadShadersFromPath("Lamp.vs", "Lamp.fs");

	InputManager::GetInstance().Start(mainWindow->GetWindow());
	CameraManager::GetInstance().GetCameras()[0]->Start(mainWindow->GetSize(), lampShader, woodenBoxMaterial.GetMaterialShader());

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	if (use2D) glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	if (use2D)
	{
		const float _vertices2D[] = {
			// positions			//normals				// colors			// textures
			 0.5f,  0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		1.0f, 0.0f, 0.0f,   1.0f, 1.0f,	 // top right
			 0.5f, -0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		0.0f, 1.0f, 0.0f,   1.0f, 0.0f,	 // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		0.0f, 0.0f, 1.0f,   0.0f, 0.0f,	 // bottom left
			-0.5f,  0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f, 1.0f,   0.0f, 1.0f,  // top left 
		};
		unsigned int _indices[] = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices2D), _vertices2D, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);
	}

	else
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
	}

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// texture coord attribute
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(3);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	if (use2D)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	}

	// Textures
	woodenBoxMaterial.LoadDiffuseTexture("WoodenBox.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	woodenBoxMaterial.LoadSpecularTexture("WoodenBox_Specular.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	woodenBoxMaterial.LoadEmissionTexture("matrix.jpg", GL_REPEAT, GL_LINEAR);

	// Shaders
	woodenBoxMaterial.InitMaterialTextures();

	if (drawLamp)
	{
		// Textures
		texture1 = LoadTexture("../Content/Textures/wall.jpg", GL_REPEAT, GL_LINEAR);
		texture2 = LoadTexture("../Content/Textures/smiley.png", GL_REPEAT, GL_LINEAR);

		// Shaders
		lampShader.Use();
		lampShader.SetInt("texture1", 0);
		lampShader.SetInt("texture2", 1);

		const FVector& _color = FVector(1.0f, 1.0f, 1.0f);
		const FVector& _position = lightPos;
		pointLight = APointLight(_color, _position, PointLightDistance::TROIS_MILLE_DEUX_CENT_CINQUANTE);
	}

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);

#pragma region Instancing


	instancingShader.LoadShadersFromPath("10.1.instancing.vs", "10.1.instancing.fs");

	int index = 0;
	float offset = 0.1f;
	for (int y = -100; y < 100; y += 2)
	{
		for (int x = -100; x < 100; x += 2)
		{
			vec2 translation;
			translation.x = (float)x / 100.0f + offset;
			translation.y = (float)y / 100.0f + offset;
			translations[index++] = translation;
		}
	}

	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * 10000, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	// also set instance data
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.

#pragma endregion


#pragma region SkyBox



#pragma endregion

}



GLuint Engine::LoadTexture(const char* _path, const int _wrapParam, const int _filterParam)
{
	GLuint _textureID;
	glGenTextures(1, &_textureID);

	int _width, _height, _channelsCount;
	unsigned char* _data = stbi_load(_path, &_width, &_height, &_channelsCount, 0);
	if (_data)
	{
		GLenum _format = GLenum();
		if (_channelsCount == 1)
			_format = GL_RED;
		else if (_channelsCount == 3)
			_format = GL_RGB;
		else if (_channelsCount == 4)
			_format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, _textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, _data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _format == GL_RGBA ? GL_CLAMP_TO_EDGE : _wrapParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _format == GL_RGBA ? GL_CLAMP_TO_EDGE : _wrapParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterParam);
	}
	else
	{
		cout << "Texture failed to load at path: " << _path << endl;
	}

	stbi_image_free(_data);
	return _textureID;
}

void Engine::Update()
{
	GLFWwindow* _window = mainWindow->GetWindow();

	CameraManager _camera = CameraManager::GetInstance();

	do
	{
		TimerManager::GetInstance().Update();
		InputManager::GetInstance().Update();
		CameraManager::GetInstance().GetCameras()[0]->Update();

		//ChangeBgColor();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

<<<<<<< HEAD
=======
		Draw();
		//instancingShader.Use();
		//glBindVertexArray(quadVAO);
		//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 10000);
		//glBindVertexArray(0);
		skybox->Update(_camera);

		mainWindow->Update();
>>>>>>> main
		glfwPollEvents();

		// Update mainWindow
		mainWindow->Update();

		// (Your code calls glfwSwapBuffers() etc.)
		glfwSwapBuffers(_window);

	} while (glfwGetKey(_window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(_window));

	glfwTerminate();
}

void Engine::ChangeBgColor()
{
	double timeValue = glfwGetTime() * 2.0;
	float greenValue = static_cast<float>(sin(timeValue / 2.0) / 2.0 + 0.5);
	float redValue = static_cast<float>(sin(timeValue * 1.2) / 2.0 + 0.5);
	float blueValue = static_cast<float>(sin(timeValue * 1.4) / 2.0 + 0.5);
	glClearColor(redValue, greenValue, blueValue, 1.0f);
}

void Engine::Draw()
{
	lampShader.Use();
	ChangeElementColor();

	multipleCubes ? DrawElements() : DrawElement();
	//if (drawLamp) DrawLamp();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Engine::ChangeElementColor()
{
	const double _timeValue = glfwGetTime() * 5.0;
	const float _redValue = static_cast<float>(sin(_timeValue) / 2.0);
	const float _greenValue = static_cast<float>(cos(_timeValue) / 2.0);
	const float _blueValue = static_cast<float>(-cos(_timeValue) / 2.0);
	lampShader.SetVec4("newColor", FVector4(_redValue, _greenValue, _blueValue, 1.0f));
}

void Engine::ApplyShader()
{

	woodenBoxMaterial.BindAndUseMaterialTextures();
	woodenBoxMaterial.SetCameraPosition(CameraManager::GetInstance().GetCameras()[0]->GetTransform()->GetLocation());
	woodenBoxMaterial.SetCurrentCurrentTime(glfwGetTime());

	// ====> light properties <====

	// == Directional light ==
	//const FVector& _direction = FVector(0.0f, 0.0f, -1.0f);
	//elementShader.SetVec3("light.direction", _direction);

	// == Point light ==
	/*elementShader.SetVec3("light.ambient", FVector(0.2f, 0.2f, 0.2f));
	elementShader.SetVec3("light.diffuse", FVector(0.5f, 0.5f, 0.5f));
	woodenBoxMaterial.GetMaterialShader().SetVec3("light.specular", FVector(1.0f, 1.0f, 1.0f));
	pointLight.SetPosition(lightPos);
	pointLight.Start(elementShader);*/

	// == Spot light ==
	CameraManager& _camera = CameraManager::GetInstance();
	woodenBoxMaterial.GetMaterialShader().SetVec3("light.position", _camera.GetCameras()[0]->GetTransform()->GetLocation());
	woodenBoxMaterial.GetMaterialShader().SetVec3("light.direction", _camera.GetCameras()[0]->GetForward());
	woodenBoxMaterial.GetMaterialShader().SetFloat("light.cutOff", cos(radians(12.5f)));
	woodenBoxMaterial.GetMaterialShader().SetFloat("light.outerCutOff", cos(radians(17.5f)));

	woodenBoxMaterial.GetMaterialShader().SetVec3("light.ambient", FVector(0.1f, 0.1f, 0.1f));
	woodenBoxMaterial.GetMaterialShader().SetVec3("light.diffuse", FVector(0.8f, 0.8f, 0.8f));
	woodenBoxMaterial.GetMaterialShader().SetVec3("light.specular", FVector(1.0f, 1.0f, 1.0f));

	woodenBoxMaterial.GetMaterialShader().SetFloat("light.constant", 1.0f);
	woodenBoxMaterial.GetMaterialShader().SetFloat("light.linear", 0.09f);
	woodenBoxMaterial.GetMaterialShader().SetFloat("light.quadratic", 0.032f);

	// material properties
	const float _intensity = 64.0f;
	woodenBoxMaterial.GetMaterialShader().SetFloat("material.shininess", _intensity);


	// render the cube
	glBindVertexArray(VAO);
	use2D ? glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0) : glDrawArrays(GL_TRIANGLES, 0, 54);
}

void Engine::DrawElement()
{
	ApplyShader();

	FMatrix _model = FMatrix::Identity;
	//_model = translate(_model, FVector(0.0f, 0.0f, -5.0f));
	_model = rotate(_model.ToMat4(), TimerManager::GetInstance().DeltaTimeSeconds(), vec3(0.0f, 1.0f, 0.0f));
	woodenBoxMaterial.GetMaterialShader().SetMat4("model", _model);
}

<<<<<<< HEAD
=======
void Engine::DrawElements()
{
	for (unsigned int _index = 0; _index < 10; _index++)
	{
		ApplyShader();

		FMatrix _model = FMatrix::Identity;
		_model = translate(_model.ToMat4(), cubePositions[_index].ToVec3());
		const float _angle = 20.0f * _index;
		_model = rotate(_model.ToMat4(), _index <= 0 ? radians(_angle) : (float)glfwGetTime(), vec3(1.0f, 0.3f, 0.5f));

		woodenBoxMaterial.GetMaterialShader().Use();
		woodenBoxMaterial.GetMaterialShader().SetMat4("model", _model);
	}
}
>>>>>>> main

void Engine::DrawLamp()
{
	lampShader.Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	const float _radius = 5.0f;
	const float _angle = glfwGetTime();
	FVector _targetLocation = cubePositions[cubeIndex];
	lightPos.X = _targetLocation.X + _radius * (float)sin(_angle);
	lightPos.Z = _targetLocation.Z + _radius * (float)cos(_angle);
	lightPos *= 0.8f;

	FMatrix _model = FMatrix::Identity;
	_model = translate(_model.ToMat4(), lightPos.ToVec3());
	_model = scale(_model.ToMat4(), vec3(0.2f));
	lampShader.SetMat4("model", _model);

	glBindVertexArray(lightVAO);
	use2D ? glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0) : glDrawArrays(GL_TRIANGLES, 0, 54);
}

<<<<<<< HEAD
void Engine::DrawElements()
{
	for (unsigned int _index = 0; _index < 10; _index++)
	{
		ApplyShader();

		FMatrix _model = FMatrix::Identity;
		_model = translate(_model.ToMat4(), cubePositions[_index].ToVec3());
		const float _angle = 20.0f * _index;
		_model = rotate(_model.ToMat4(), _index <= 0 ? radians(_angle) : (float)glfwGetTime(), vec3(1.0f, 0.3f, 0.5f));

			elementShader.Use();
			elementShader.SetMat4("model", _model);
	}
}

=======
>>>>>>> main
void Engine::Stop()
{
	mainWindow->Stop();
	ClearElements();
}

void Engine::ClearElements()
{
	// Cleanup VBO
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &quadVAO);
	glDeleteBuffers(1, &quadVBO);


	lampShader.ClearShader();
	woodenBoxMaterial.GetMaterialShader().ClearShader();
}

void Engine::Launch()
{
	Start();
	Update();
	Stop();
}

FVector Engine::GetNextCubePosition()
{
	if (!multipleCubes) return FVector();

	cubeIndex++;
	cubeIndex %= 10;
	return cubePositions[cubeIndex];
}

// La lumière n'a pas ses textures