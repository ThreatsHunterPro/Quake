#pragma once 
#include "..\..\CoreMinimal.h"
#include "CustomShader.h"

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
	vec3 position;
	vec3 targetLocation;

	// FoV
	float fov;
	float minFov;
	float maxFov;

	// Ranges
	float nearRange;
	float farRange;

	// Vectors
	vec3 forward;
	vec3 right;
	vec3 up;

	// MVP
	mat4 projection;
	mat4 view;

	// Render
	vec2 windowSize;
	CustomShader shader;
	CustomShader lighting;

public:
	FORCEINLINE void SetMoveView(const bool _status)
	{
		moveView = _status;
	}
	FORCEINLINE void SetTargetLocation(const vec3& _location)
	{
		targetLocation = _location;
	}
	FORCEINLINE static CameraManager& GetInstance()
	{
		static CameraManager _instance;
		return _instance;
	}
	FORCEINLINE const vec3& GetPosition() const
	{
		return position;
	}
	FORCEINLINE const vec3& GetForward() const
	{
		return forward;
	}
	FORCEINLINE const mat4& GetProjectionMatrix(bool _inPerspective = true)
	{
		if (_inPerspective)
		{
			return projection = perspective(radians(fov), static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y), nearRange, 100.0f);
		}

		return projection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearRange, farRange);
	}
	FORCEINLINE const mat4& GetViewMatrix()
	{
		return view = lookAt(position, position + forward, up);
	}

public:
	CameraManager();

private:
	void InitDepth();
	void UpdateCameraVectors();

public:
	void Start(const vec2& _windowSize, const CustomShader& _shader, const CustomShader& _lighting);
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