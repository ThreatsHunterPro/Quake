
#include "../../Core/Math/FVector/TVector.h"
#include "../../Core/Math/FMatrix.h"
#include "../../Core/Math/TTransform.h"
#include "../../../Editor/Engine/Shader/CustomShader.h"


class UCamera
{
	FTransform* transform;

	// VALUES
	float speed;
	float sensivity;
	FVector targetLocation;

	// FOV
	float fov;
	float minFov;
	float maxFov;

	// RANGE
	float nearRange;
	float farRange;

	// STATES
	bool moveView;

	// VECTORS
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
	FORCEINLINE FTransform* GetTransform() const
	{
		return transform;
	}
	FORCEINLINE  FVector& GetForward() 
	{
		return forward;
	}
	FORCEINLINE  FVector& GetUp() 
	{
		return up;
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
		return view = lookAt(transform->GetLocation().ToVec3(), transform->GetLocation().ToVec3() + forward.ToVec3(), up.ToVec3());
	}

public:
	UCamera();
	~UCamera();
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