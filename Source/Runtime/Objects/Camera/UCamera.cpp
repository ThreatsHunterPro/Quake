#include "UCamera.h"
#include "../../Managers/TimerManager.h"
#include "../../Managers/CameraManager.h"

UCamera::UCamera()
{
	transform = new FTransform();
	// States
	moveView = true;

	// Values
	speed = 3.0f;
	sensivity = 0.05f;

	// Positions
	targetLocation = transform->GetLocation() + forward;

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
	shader = CustomShader();



	CameraManager::GetInstance().Register(this);
}

UCamera::~UCamera()
{
	delete transform;
	transform = nullptr;
}

void UCamera::InitDepth()
{
	glEnable(GL_DEPTH_TEST);
}

void UCamera::UpdateCameraVectors()
{


	forward = FVector(
		FMath::Cos(transform->GetRotation().X) * FMath::Sin(transform->GetRotation().Y),
		FMath::Sin(transform->GetRotation().X),
		FMath::Cos(transform->GetRotation().X) * FMath::Cos(transform->GetRotation().Y)
	);

	right = FVector(
		FMath::Sin(transform->GetRotation().Y - 90.0f),
		0,
		FMath::Cos(transform->GetRotation().Y - 90.0f)
	);

	up = right.CrossProduct(forward);
}

void UCamera::Start(const FVector2& _windowSize, const CustomShader& _shader, const CustomShader& _lighting)
{
	windowSize = _windowSize;
	shader = _shader;
	lighting = _lighting;

	InitDepth();
}

void UCamera::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	UpdateCameraVectors();

	if (moveView)
	{
		const float _radius = 5.0f;
		const float _angle = glfwGetTime();
		const float _camX = targetLocation.X + _radius * (float)FMath::Sin(_angle);
		const float _camZ = targetLocation.Z + _radius * (float)FMath::Cos(_angle);
		view = lookAt(vec3(_camX, 2.0f, _camZ), targetLocation.ToVec3(), vec3(0.0f, 1.0f, 0.0f));
	}
	else view = lookAt(transform->GetLocation().ToVec3(), transform->GetLocation().ToVec3() + forward.ToVec3(), up.ToVec3());

	projection = perspective(FMath::DegreesToRadians(fov), (float)windowSize.X / (float)windowSize.Y, 0.1f, 100.0f);

	shader.Use();
	shader.SetMat4("view", view);
	shader.SetMat4("projection", projection);

	lighting.Use();
	lighting.SetMat4("view", view);
	lighting.SetMat4("projection", projection);
}

void UCamera::MoveForward(float _forwardValue)
{
	const float _value = FMath::Clamp(_forwardValue, -1.0f, 1.0f);
	transform->Translation += forward * _value * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}

void UCamera::MoveRight(float _rightValue)
{
	const float _value = FMath::Clamp(_rightValue, -1.0f, 1.0f);
	transform->Translation += right * _rightValue * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}

void UCamera::MoveUp(float _upValue)
{
	const float _value = FMath::Clamp(_upValue, -1.0f, 1.0f);
	transform->Translation += up * _value * speed * TimerManager::GetInstance().DeltaTimeSeconds();
}

void UCamera::MoveYaw(float _value)
{
	transform->Rotation.Y += FMath::DegreesToRadians(_value * sensivity);
}

void UCamera::MovePitch(float _value)
{
	transform->Rotation.X += FMath::DegreesToRadians(_value * sensivity);
	transform->Rotation.X = FMath::Clamp(transform->Rotation.X, -90.0f, 90.0f);
}

void UCamera::MoveRoll(float _value)
{
	transform->Rotation.Z += _value * sensivity * TimerManager::GetInstance().DeltaTimeSeconds();

}

void UCamera::RotateAround(float _direction)
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

void UCamera::Zoom(float _value)
{
	fov -= _value;
	fov = FMath::Clamp(fov, minFov, maxFov);
}
