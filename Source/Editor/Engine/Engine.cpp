#include "Engine.h"
#include "..\..\Runtime\Managers\InputManager.h"
#include "..\..\Runtime\Managers\CameraManager.h"
#include "..\..\Runtime\Managers\TimerManager.h"

Engine::Engine()
{
	mainWindow = new EngineWindow();

	VAO = GLuint();
	VBO = GLuint();
	EBO = GLuint();
	quadVAO = GLuint();
	quadVBO = GLuint();
	shadowFBO = GLuint();
	shadowMap = GLuint();
	texture1 = GLuint();
	texture2 = GLuint();
	elementShader = new CustomShader();

	use2D = false;
	rotateElements = false;
	multipleCubes = true;

	cubeIndex = 0;

	// Lamp
	drawLamp = true;
	moveLamp = true;
	rotateLamp = false;
	lightVAO = GLuint();
	lightPos = FVector(-2.0f, 4.0f, -1.0f);
	diffuseMap = GLuint();
	specularMap = GLuint();
	emissionMap = GLuint();
	lampShader = new CustomShader();
	shadowShader = new CustomShader();
	debugShader = new CustomShader();
	near_plane = 1.0f;
	far_plane = 7.5f;
}

Engine::~Engine()
{
	delete mainWindow;
	delete elementShader;
	delete lampShader;
	delete shadowShader;
	delete debugShader;
}

void Engine::Start()
{
	mainWindow->Start();

	// Shaders
	elementShader->LoadShadersFromPath("Element.vs", "Element.fs");
	lampShader->LoadShadersFromPath("Lamp.vs", "Lamp.fs");
	shadowShader->LoadShadersFromPath("Shadow.vs", "Shadow.fs");
	debugShader->LoadShadersFromPath("Debug.vs", "Debug.fs");
	vector<CustomShader*> shaders = { elementShader, lampShader, };

	InputManager::GetInstance().Start(mainWindow->GetWindow());
	CameraManager::GetInstance().Start(mainWindow->GetSize(), shaders);

	// Textures
	diffuseMap = LoadTexture("../Content/Textures/WoodenBox.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	specularMap = LoadTexture("../Content/Textures/WoodenBox_Specular.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	emissionMap = LoadTexture("../Content/Textures/matrix.jpg", GL_REPEAT, GL_LINEAR);

#pragma region Cube VAO

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
#pragma endregion

#pragma region Quad VAO
	float quadVertices[] = {
		// positions			// texture Coords
		-0.8f, -0.95f, 0.0f,		1.0f, 0.0f,
		-0.95f, -0.95f, 0.0f,		0.0f, 0.0f,
		-0.8f, -0.8f, 0.0f,			1.0f, 1.0f,
		-0.95f, -0.8f, 0.0f,		0.0f, 1.0f,
	};
	// setup plane VAO
	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
#pragma endregion

#pragma region Depth map
	// create FBO
	glGenFramebuffers(1, &shadowFBO);
	// create depth buffer
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); 

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

	// Disable color buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// check buffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "Framebuffer not OK" << endl;
		return;
	}
#pragma endregion

	// Shaders
	elementShader->Use();
	elementShader->SetInt("shadowMap", 0);
	elementShader->SetInt("material.diffuse", 1);
	elementShader->SetInt("material.specular", 2);
	elementShader->SetInt("material.emission", 3);
	debugShader->Use();
	debugShader->SetInt("depthMap", 0);

	if (drawLamp)
	{
		FVector& _color = FVector(1.0f, 1.0f, 1.0f);
		const FVector& _position = lightPos;
		const FVector& _direction = FVector(0.0f, -1.0f, 0.0f);

		lampShader->Use();
		lampShader->SetVec3("newColor", _color);

		//Directional light
		directionalLight = new ADirectionalLight(_color, _direction);
		directionalLight->SetPhong(_color * 0.1f, _color, _color);
		directionalLight->SetShader(elementShader);
		//Point light
		pointLight = new APointLight(_color, _position, PointLightDistance::TRENTE_DEUX);
		pointLight->SetPhong(_color * 0.05f, _color * 0.8f, _color);
		pointLight->SetShader(elementShader);
		//SPot light
		spotLight = new ASpotLight(_color, _position, PointLightDistance::CINQUANTE, 12.5f, 15.0f);
		spotLight->SetPhong(_color * 0.0f, _color, _color);
		spotLight->SetShader(elementShader);
	}
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, _width, _height, 0, _format, GL_UNSIGNED_BYTE, _data); //internalFormat = GL_SRGB because of gamma corection
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapParam);
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

	do
	{
		TimerManager::GetInstance().Update();
		InputManager::GetInstance().Update();
		CameraManager::GetInstance().Update();

		//ChangeBgColor();
		Draw();

		glfwSwapBuffers(_window);
		glfwPollEvents();

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
	lampShader->Use();
	ChangeElementColor();

	// 1. render depth of scene to texture (from light's perspective)
	ApplyShadow();
	// 2. render scene as normal using the generated depth/shadow map  
	ApplyShader();

	debugShader->Use();
	debugShader->SetFloat("near_plane", near_plane);
	debugShader->SetFloat("far_plane", far_plane);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if (drawLamp) DrawLamp();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Engine::ChangeElementColor()
{
	const double _timeValue = glfwGetTime() * 5.0;
	const float _redValue = static_cast<float>(sin(_timeValue) / 2.0);
	const float _greenValue = static_cast<float>(cos(_timeValue) / 2.0);
	const float _blueValue = static_cast<float>(-cos(_timeValue) / 2.0);
	lampShader->SetVec4("newColor", FVector4(_redValue, _greenValue, _blueValue, 1.0f));
}

void Engine::ApplyShadow()
{
	// binding buffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shadowFBO);
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glClear(GL_DEPTH_BUFFER_BIT);
	shadowShader->Use();

	FMatrix lightProjection, lightView;
	//lightProjection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 20.0f);
	lightProjection = perspective(45.0f, 1920.f / 1080.f, near_plane, far_plane);
	lightView = lookAt(lightPos.ToVec3(), vec3(0.0f), vec3(0.0, -1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView * FMatrix::Identity;
	// render scene from light's point of view
	shadowShader->SetMat4("lightSpaceMatrix", lightSpaceMatrix);

	// bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	// bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	// bind emission map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, emissionMap);

	// render the cube
	RenderScene(shadowShader);
}

void Engine::ApplyShader()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, mainWindow->GetSize().X, mainWindow->GetSize().Y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	elementShader->Use();

	// bind shadow map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, shadowMap);

	// bind diffuse map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);

	// bind specular map
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, specularMap);

	// bind emission map
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, emissionMap);

	// main properties
	elementShader->SetVec3("viewPos", CameraManager::GetInstance().GetPosition());
	elementShader->SetVec3("lightPos", lightPos);
	elementShader->SetMat4("lightSpaceMatrix", lightSpaceMatrix);

	FMatrix lightProjection, lightView;
	//lightProjection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 20.0f);
	lightProjection = perspective(45.0f, 1920.f / 1080.f, near_plane, far_plane);
	lightView = lookAt(lightPos.ToVec3(), vec3(0.0f), vec3(0.0, -1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView * FMatrix::Identity;
	// render scene from light's point of view
	shadowShader->SetMat4("lightSpaceMatrix", lightSpaceMatrix);

	// == Directional light ==
	const FVector& _direction = FVector(0.0f, -1.0f, 0.0f);
	//directionalLight->Update(0);

	// == Point light ==
	pointLight->SetPosition(lightPos); 
	pointLight->Update(0);

	// == Spot light / Flash light ==
	CameraManager& _camera = CameraManager::GetInstance();
	spotLight->SetPosition(_camera.GetPosition());
	spotLight->SetDirection(_camera.GetForward());
	//spotLight->Update(0);

	// material properties
	const float _intensity = 64.0f; //multiply *2 because of Blinn-Phong
	elementShader->SetFloat("material.shininess", _intensity);

	// render the cube
	RenderScene(elementShader);
}

void Engine::RenderScene(CustomShader* _shader)
{
	//Cube(s)
	multipleCubes ? DrawElements(_shader) : DrawElement(_shader);
}

void Engine::DrawElement(CustomShader* _shader)
{
	FMatrix _model = FMatrix::Identity;
	_model = translate(_model.ToMat4(), FVector(0.0f, 0.0f, -5.0f).ToVec3());
	//_model = rotate(_model.ToMat4(), TimerManager::GetInstance().DeltaTimeSeconds(), vec3(0.0f, 1.0f, 0.0f));
	_shader->Use();
	_shader->SetMat4("model", _model);

	// render the cube
	glBindVertexArray(VAO);
	use2D ? glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0) : glDrawArrays(GL_TRIANGLES, 0, 54);
	glBindVertexArray(0);
}

void Engine::DrawElements(CustomShader* _shader)
{
	for (unsigned int _index = 0; _index < 5; _index++)
	{
		FMatrix _model = FMatrix::Identity;
		_model = translate(_model.ToMat4(), cubePositions[_index].ToVec3());

		//const float _angle = 20.0f * _index;
		//_model = rotate(_model.ToMat4(), _index <= 0 ? radians(_angle) : (float)glfwGetTime(), vec3(1.0f, 0.3f, 0.5f));

		_shader->Use();
		_shader->SetMat4("model", _model);

		// render the cube
		glBindVertexArray(VAO);
		use2D ? glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0) : glDrawArrays(GL_TRIANGLES, 0, 54);
		glBindVertexArray(0);
	}
}

void Engine::DrawLamp()
{
	lampShader->Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	if (moveLamp)
	{
		const float _radius = 5.0f;
		const float _angle = glfwGetTime();
		FVector _targetLocation = cubePositions[cubeIndex];
		lightPos.X = _targetLocation.X + _radius * (float)sin(_angle);
		lightPos.Z = _targetLocation.Z + _radius * (float)cos(_angle);
		lightPos *= 0.8f;
	}

	FMatrix _model = FMatrix::Identity;
	_model = translate(_model.ToMat4(), lightPos.ToVec3());
	_model = scale(_model.ToMat4(), vec3(0.2f));
	lampShader->SetMat4("model", _model);

	glBindVertexArray(lightVAO);
	use2D ? glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0) : glDrawArrays(GL_TRIANGLES, 0, 54);
}

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

	lampShader->ClearShader();
	elementShader->ClearShader();
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