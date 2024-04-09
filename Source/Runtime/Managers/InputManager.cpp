#include "InputManager.h"
#include "CameraManager.h"
#include "..\..\Editor\Engine\Engine.h"
#include "..\Core\Math\FVector\TVector.h"

InputManager::InputManager()
{
	window = nullptr;
	previousCursorPos = FVector2();
}

void InputManager::AddMapping(InputMapping* _mapping)
{
	allMappings.Add(_mapping);
}

void InputManager::ClearMappings()
{
	allMappings.Empty();
}


void InputManager::Start(sf::RenderWindow* _window)
{
	window = _window;
	
	InitControls();

	const FVector& _cubePosition = Engine::GetInstance().GetNextCubePosition();
	CameraManager::GetInstance().SetTargetLocation(_cubePosition);
	//glfwSetWindowUserPointer(window, this);
}

void InputManager::Update()
{
	glfwPollEvents();

	ProcessMouse();
	ProcessInputs();
}

void InputManager::InitControls() const
{

	BindCallbacks();

	//glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwPollEvents();

	int _windowWidth = window->getSize().x, _windowHeight = window->getSize().y;
 
	//glfwGetWindowSize(window, &_windowWidth, &_windowHeight);

	const double _halfWidth = _windowWidth / 2.0;
	const double _halfHeight = _windowHeight / 2.0;
	//glfwSetCursorPos(window, _halfWidth, _halfHeight);
}

void InputManager::BindCallbacks() const
{
	//glfwSetScrollCallback(window, genericCallback(InputManager, onWindowScrollCallback));
}

void InputManager::ProcessMouse()
{
	//double _xPos, yPos = 0.0;
	//glfwGetCursorPos(window, &_xPos, &yPos);

	//const float _xCursorPos = static_cast<float>(_xPos);
	//const float _yCursorPos = static_cast<float>(yPos);

	//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	//{
	//	const float yawValue = previousCursorPos.X - _xCursorPos;
	//	const float pitchValue = previousCursorPos.Y - _yCursorPos;

	//	CameraManager::GetInstance().MoveYaw(yawValue);
	//	CameraManager::GetInstance().MovePitch(pitchValue);
	//}

	//previousCursorPos = FVector2(_xCursorPos, _yCursorPos);
}
//TODO fix inputs
void InputManager::ProcessInputs() const
{
	sf::Event _event;
	while (window->pollEvent(_event))
	{
		if (_event.type == sf::Event::Closed)
		{
			window->close();
		}
		if (_event.type == sf::Event::KeyPressed)
		{
			if (_event.key.code == sf::Keyboard::Z)
			{
				CameraManager::GetInstance().MoveForward(1.0f);

			}
			if (_event.key.code == sf::Keyboard::D)
			{
				CameraManager::GetInstance().MoveRight(1.0f);

			}
			if (_event.key.code == sf::Keyboard::Q)
			{
				CameraManager::GetInstance().MoveRight(-1.0f);

			}
			if (_event.key.code == sf::Keyboard::S)
			{
				CameraManager::GetInstance().MoveForward(-1.0f);

			}
			if (_event.key.code == sf::Keyboard::C)
			{
				const FVector& _cubePosition = Engine::GetInstance().GetNextCubePosition();
				CameraManager::GetInstance().SetTargetLocation(_cubePosition);



			}
			if (_event.key.code == sf::Keyboard::V)
			{
				CameraManager::GetInstance().SetMoveView(true);
				const FVector& _cubePosition = Engine::GetInstance().GetNextCubePosition();
				CameraManager::GetInstance().SetTargetLocation(_cubePosition);

			}
			if (_event.key.code == sf::Keyboard::B)
			{
				CameraManager::GetInstance().SetMoveView(false);


			}
			if (_event.key.code == sf::Keyboard::Space)
			{
				CameraManager::GetInstance().MoveUp(1.0f); 
			}
			if (_event.key.code == sf::Keyboard::LAlt)
			{
				CameraManager::GetInstance().MoveUp(-1.0f);



			}
		}
	}
	/*
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		CameraManager::GetInstance().MoveForward(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		CameraManager::GetInstance().MoveForward(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CameraManager::GetInstance().MoveRight(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CameraManager::GetInstance().MoveRight(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		CameraManager::GetInstance().MoveUp(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		CameraManager::GetInstance().MoveUp(1.0f);
	}

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
	{
		const FVector& _cubePosition = Engine::GetInstance().GetNextCubePosition();
		CameraManager::GetInstance().SetTargetLocation(_cubePosition);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		CameraManager::GetInstance().SetMoveView(true);
		const FVector& _cubePosition = Engine::GetInstance().GetNextCubePosition();
		CameraManager::GetInstance().SetTargetLocation(_cubePosition);
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		CameraManager::GetInstance().SetMoveView(false);
	}*/
}

void InputManager::Scroll(double xoffset, double yoffset)
{
	std::cout << "scroll" << std::endl;
	//camera.ProcessMouseScroll(static_cast<float>(yoffset));
}