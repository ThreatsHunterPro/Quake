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
	position = FVector(0.0f, 0.0f, 5.0f);
	targetLocation = position + forward;

	// FoV
	fov = 45.0f;
	minFov = 0.1f;
	maxFov = 100.0f;

	// Ranges
	nearRange = 0.1f;
	farRange = 45.0f;

	// Vectors
	forward = FVector(0.0f, 0.0f, -1.0f);
	right = FVector(1.0f, 0.0f, 0.0f);
	up = FVector(0.0f, 1.0f, 0.0f);

	// MVP
	projection = FMatrix::Identity;
	view = FMatrix::Identity;

	// Render
	windowSize = FVector2();
}

// Start
void CameraManager::Start(const FVector2& _windowSize, const vector<CustomShader>& _shaders)
{
	windowSize = _windowSize;
	shaders = _shaders;

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
		const float _camX = targetLocation.X + _radius * (float)FMath::Sin(_angle);
		const float _camZ = targetLocation.Z + _radius * (float)FMath::Cos(_angle);
		view = lookAt(vec3(_camX, 2.0f, _camZ), targetLocation.ToVec3(), vec3(0.0f, 1.0f, 0.0f));
	}
	else
	{
		view = lookAt(position.ToVec3(), position.ToVec3() + forward.ToVec3(), up.ToVec3());
	}

	projection = perspective(FMath::DegreesToRadians(fov), (float)windowSize.X / (float)windowSize.Y, 0.1f, 100.0f);

	size_t _size = shaders.size();
	for (size_t i = 0; i < _size; i++)
	{
 		shaders[i].Use();
		shaders[i].SetMat4("view", view);
		shaders[i].SetMat4("projection", projection);
	}
}
void CameraManager::UpdateCameraVectors()
{
	forward = FVector(
		FMath::Cos(pitch) * FMath::Sin(yaw),
		FMath::Sin(pitch),
		FMath::Cos(pitch) * FMath::Cos(yaw)
	);

	right = FVector(
		FMath::Sin(yaw - 90.0f),
		0,
		FMath::Cos(yaw - 90.0f)
	);

	up = right.CrossProduct(forward);
}

// Standard
void CameraManager::MoveForward(float _forwardValue)
{
	const float _value = FMath::Clamp(_forwardValue, -1.0f, 1.0f);
	position += forward * _value * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}
void CameraManager::MoveRight(float _rightValue)
{
	const float _value = FMath::Clamp(_rightValue, -1.0f, 1.0f);
	position += right * _rightValue * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}
void CameraManager::MoveUp(float _upValue)
{
	const float _value = FMath::Clamp(_upValue, -1.0f, 1.0f);
	position += up * _value * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}

// Mouse
void CameraManager::MoveYaw(float _value)
{
	yaw += FMath::DegreesToRadians(_value * sensivity);

	yaw = mod(yaw, 360.0f);
	if (yaw > 180.0f)
	{
		yaw -= 360.0f;
	}
}
void CameraManager::MovePitch(float _value)
{
	pitch += FMath::DegreesToRadians(_value * sensivity);
	pitch = FMath::Clamp(pitch, -90.0f, 90.0f);
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
	fov = FMath::Clamp(fov, minFov, maxFov);
}