#include "CameraManager.h"
#include "TimerManager.h"

CameraManager::CameraManager()
{
	// States
	moveView = true;

	// Values
	yaw = -90.0f;
	pitch = 0.0f;
	roll = 0.0f;
	angle = 0.0f;
	speed = 3.0f;
	sensivity = 0.05f;

	// Positions
	position = vec3(0.0f, 0.0f, 5.0f);
	targetLocation = position + forward;

	// FoV
	fov = 45.0f;
	minFov = 0.1f;
	maxFov = 100.0f;

	// Ranges
	nearRange = 0.1f;
	farRange = 45.0f;

	// Vectors
	forward = vec3(0.0f, 0.0f, -1.0f);
	right = vec3(1.0f, 0.0f, 0.0f);
	up = vec3(0.0f, 1.0f, 0.0f);

	// MVP
	projection = mat4(1.0f);
	view = mat4(1.0f);

	// Render
	windowSize = vec2();
	shader = CustomShader();
}

// Start
void CameraManager::Start(const vec2& _windowSize, const CustomShader& _shader, const CustomShader& _lighting)
{
	windowSize = _windowSize;
	shader = _shader;
	lighting = _lighting;

	InitDepth();
}
void CameraManager::InitDepth()
{
	glEnable(GL_DEPTH_TEST);
	/*glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);*/
}

// Update
void CameraManager::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//UpdateCameraVectors();

	if (moveView)
	{
		const float _radius = 5.0f;
		const float _angle = glfwGetTime();
		const float _camX = targetLocation.x + _radius * (float)sin(_angle);
		const float _camZ = targetLocation.z + _radius * (float)cos(_angle);
		view = lookAt(vec3(_camX, 2.0f, _camZ), targetLocation, vec3(0.0f, 1.0f, 0.0f));
	}

	else
	{
		view = lookAt(position, position + forward, up);
	}

	projection = perspective(radians(fov), (float)windowSize.x / (float)windowSize.y, 0.1f, 100.0f);

	shader.Use();
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);

	lighting.Use();
	lighting.SetMat4("view", view);
	lighting.SetMat4("projection", projection);
}
void CameraManager::UpdateCameraVectors()
{
	forward = vec3(
		cos(pitch) * sin(yaw),
		sin(pitch),
		cos(pitch) * cos(yaw)
	);

	right = vec3(
		sin(yaw - 90.0f),
		0,
		cos(yaw - 90.0f)
	);

	up = cross(right, forward);
}

// Standard
void CameraManager::MoveForward(float _forwardValue)
{
	const float _value = clamp(_forwardValue, -1.0f, 1.0f);
	position += forward * _value * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}
void CameraManager::MoveRight(float _rightValue)
{
	const float _value = clamp(_rightValue, -1.0f, 1.0f);
	position += right * _rightValue * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}
void CameraManager::MoveUp(float _upValue)
{
	const float _value = clamp(_upValue, -1.0f, 1.0f);
	position += up * _value * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}

// Mouse
void CameraManager::MoveYaw(float _value)
{
	yaw += radians(_value * sensivity);

	yaw = mod(yaw, 360.0f);
	if (yaw > 180.0f)
	{
		yaw -= 360.0f;
	}
}
void CameraManager::MovePitch(float _value)
{
	pitch += radians(_value * sensivity);
	pitch = clamp(pitch, -90.0f, 90.0f);
}
void CameraManager::MoveRoll(float _value)
{
	roll += _value * sensivity * TimerManager::GetInstance().DeltaTimeSeconds();

	// if (roll >= 360.0f)
	// 	roll = 0.0f;
	//
	// else if (roll < 0.0f)
	// 	roll = 360.0f;
}

// Other
void CameraManager::RotateAround(float _direction)
{
	// const float _value = std::clamp(_direction, -1.0f, 1.0f);
	// angle += _value * speed / 10 * TimerManager::GetInstance().DeltaTimeSeconds();
	//
	// if (angle >= 360.0f)
	// 	angle = 0.0f;
	// else if (angle < 0.0f)
	// 	angle = 360.0f;
	//
	// position.x = cos(radians(angle)) * cos(radians(pitch));
	// position.y = sin(radians(pitch));
	// position.z = sin(radians(angle)) * cos(radians(pitch));
}
void CameraManager::Zoom(float _value)
{
	fov -= _value;
	fov = clamp(fov, minFov, maxFov);
}