#pragma once 
#include "..\..\CoreMinimal.h"
#include "..\..\Editor\Engine\Shader\CustomShader.h"
#include "..\Core\Math\FVector\TVector.h"
#include "..\Core\Math\FVector\FVector2.h"
#include "..\Core\Math\FVector\FVector4.h"

class CameraManager
{
	// States
	bool moveView;

	// Values
	float yaw;
	float pitch;
	float roll;
	float angle;
	float speed;
	float sensivity;

	// Positions
	FVector position;
	FVector targetLocation;

	// FoV
	float fov;
	float minFov;
	float maxFov;

	// Ranges
	float nearRange;
	float farRange;

	// Vectors
	FVector forward;
	FVector right;
	FVector up;

	// MVP
	FMatrix projection;
	FMatrix view;

	// Render
	FVector2 windowSize;
	CustomShader shader;
	CustomShader lighting;

public:
	FORCEINLINE void SetMoveView(const bool _status)
	{
		moveView = _status;
	}
	FORCEINLINE void SetTargetLocation(const FVector& _location)
	{
		targetLocation = _location;
	}
	FORCEINLINE static CameraManager& GetInstance()
	{
		static CameraManager _instance;
		return _instance;
	}
	FORCEINLINE const FVector& GetPosition() const
	{
		return position;
	}
	FORCEINLINE const FVector& GetForward() const
	{
		return forward;
	}
	FORCEINLINE const FMatrix& GetProjectionMatrix(bool _inPerspective = true)
	{
		if (_inPerspective)
		{
			return projection = perspective(FMath::DegreesToRadians(fov), static_cast<float>(windowSize.X) / static_cast<float>(windowSize.Y), nearRange, 100.0f);
		}

		return projection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearRange, farRange);
	}
	FORCEINLINE const FMatrix& GetViewMatrix()
	{
		return view = lookAt(position.ToVec3(), position.ToVec3() + forward.ToVec3(), up.ToVec3());
	}

public:
	CameraManager();

private:
	void InitDepth();
	void UpdateCameraVectors();

public:
	void Start(const FVector2& _windowSize, const CustomShader& _shader, const CustomShader& _lighting);
	void Update();

	// Standard
	void MoveForward(float _forwardValue);
	void MoveRight(float _rightValue);
	void MoveUp(float _upValue);

	// Mouse
	void MoveYaw(float _value);
	void MovePitch(float _value);
	void MoveRoll(float _value);

	// Other
	void RotateAround(float _direction);
	void Zoom(float _value);
};