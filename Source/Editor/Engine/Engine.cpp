#include "Engine.h"
#include "..\..\Runtime\Managers\InputManager.h"
#include "..\..\Runtime\Managers\CameraManager.h"
#include "..\..\Runtime\Managers\TimerManager.h"
#include "../../Runtime/Objects/Actors/AActor.h"
#include "../../Runtime/Objects/Mesh/UPrimitiveMesh.h"
#include "../../Runtime/Objects/Mesh/UStaticMeshComponent.h"


Engine::Engine()
{
	mainWindow = new EngineWindow();
	actor = nullptr;
	VAO = GLuint();
	VBO = GLuint();
	EBO = GLuint();
	texture1 = GLuint();
	texture2 = GLuint();
	elementShader = CustomShader();

	use2D = false;
	rotateElements = false;
	multipleCubes = true;

	cubeIndex = 0;

	// Lamp
	drawLamp = false;
	moveLamp = true;
	rotateLamp = false;
	lightVAO = GLuint();
	lightPos = FVector(0.5f, 0.5f, 1.0f);
	diffuseMap = GLuint();
	specularMap = GLuint();
	emissionMap = GLuint();
	lampShader = CustomShader();
}

Engine::~Engine()
{
	delete mainWindow, actor;
}


void Engine::Start()
{
	mainWindow->Start();

	// Shaders
	elementShader.LoadShadersFromPath("Element.vs", "Element.fs");
	lampShader.LoadShadersFromPath("Lamp.vs", "Lamp.fs");

	InputManager::GetInstance().Start(mainWindow->GetWindow());
	CameraManager::GetInstance().Start(mainWindow->GetSize(), lampShader, elementShader);
	//actor = new AActor("Loul", new UStaticMesh());


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//Plane
	if (use2D) glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	if (use2D)
	{
		TArray<float> _vertices2D = {
			// positions			//normals				// colors			// textures
			 0.5f,  0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		1.0f, 0.0f, 0.0f,   1.0f, 1.0f,	 // top right
			 0.5f, -0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		0.0f, 1.0f, 0.0f,   1.0f, 0.0f,	 // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		0.0f, 0.0f, 1.0f,   0.0f, 0.0f,	 // bottom left
			-0.5f,  0.5f, 0.0f,		0.0f,  0.0f, -1.0f,		1.0f, 1.0f, 1.0f,   0.0f, 1.0f,  // top left 
		};
	
		TArray<float>  _indices = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};
		
		glBufferData(GL_ARRAY_BUFFER, _vertices2D.Num() * sizeof(float), _vertices2D.GetArray(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.Num() * sizeof(float), _indices.GetArray(), GL_STATIC_DRAW);
	}
	else
	{
		TArray<float> _vertices = {//position		 // normals		    // color	      // texture
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0
	};
		glBufferData(GL_ARRAY_BUFFER, _vertices.Num() * sizeof(float), _vertices.GetArray(), GL_STATIC_DRAW);
	}
	
	//position attribute
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
	
	 //Textures
	diffuseMap = LoadTexture("../Content/Textures/WoodenBox.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	specularMap = LoadTexture("../Content/Textures/WoodenBox_Specular.png", GL_CLAMP_TO_EDGE, GL_LINEAR);
	emissionMap = LoadTexture("../Content/Textures/matrix.jpg", GL_REPEAT, GL_LINEAR);
	
	 //Shaders
	elementShader.Use();
	elementShader.SetInt("material.diffuse", 0);
	elementShader.SetInt("material.specular", 1);
	elementShader.SetInt("material.emission", 2);

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
		
		//actor->GetStaticMesh()->DrawElement();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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
	lampShader.Use();
	ChangeElementColor();

	multipleCubes ? DrawElements() : DrawElement();
	if (drawLamp) DrawLamp();

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
	elementShader.Use();

	// main properties
	elementShader.SetVec3("viewPos", CameraManager::GetInstance().GetPosition());
	elementShader.SetFloat("time", glfwGetTime());

	// ====> light properties <====

	// == Directional light ==
	//const FVector& _direction = FVector(0.0f, 0.0f, -1.0f);
	//elementShader.SetVec3("light.direction", _direction);

	// == Point light ==
	/*elementShader.SetVec3("light.ambient", FVector(0.2f, 0.2f, 0.2f));
	elementShader.SetVec3("light.diffuse", FVector(0.5f, 0.5f, 0.5f));
	elementShader.SetVec3("light.specular", FVector(1.0f, 1.0f, 1.0f));
	pointLight.SetPosition(lightPos);
	pointLight.Start(elementShader);*/

	// == Spot light ==
	CameraManager& _camera = CameraManager::GetInstance();
	elementShader.SetVec3("light.position", _camera.GetPosition());
	elementShader.SetVec3("light.direction", _camera.GetForward());
	elementShader.SetFloat("light.cutOff", cos(radians(12.5f)));
	elementShader.SetFloat("light.outerCutOff", cos(radians(17.5f)));

	elementShader.SetVec3("light.ambient", FVector(0.1f, 0.1f, 0.1f));
	elementShader.SetVec3("light.diffuse", FVector(0.8f, 0.8f, 0.8f));
	elementShader.SetVec3("light.specular", FVector(1.0f, 1.0f, 1.0f));

	elementShader.SetFloat("light.constant", 1.0f);
	elementShader.SetFloat("light.linear", 0.09f);
	elementShader.SetFloat("light.quadratic", 0.032f);

	// material properties
	const float _intensity = 64.0f;
	elementShader.SetFloat("material.shininess", _intensity);

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
	glBindVertexArray(VAO);
	use2D ? glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0) : glDrawArrays(GL_TRIANGLES, 0, 54);
}

void Engine::DrawElement()
{
	ApplyShader();

	FMatrix _model = FMatrix::Identity;
	//_model = translate(_model, FVector(0.0f, 0.0f, -5.0f));
	_model = rotate(_model.ToMat4(), TimerManager::GetInstance().DeltaTimeSeconds(), vec3(0.0f, 1.0f, 0.0f));
	elementShader.SetMat4("model", _model);
}

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

	lampShader.ClearShader();
	elementShader.ClearShader();
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