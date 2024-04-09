#pragma once
#include "../../../CoreMinimal.h"
#include "../../Objects/Components/UActorComponent.h"

#define UE_KINDA_SMALL_NUMBER (1.e-4f)

class USpringArmComponent : public UActorComponent
{




public:
	int bEnableCameraLag : 1;
	int bInheritPitch : 1;
	int bInheritRoll : 1;
	int bInheritYaw : 1;
	bool bIsCameraFixed = false;
	bool bUseCameraLagSubstepping = true;
private:
	float CameraLagMaxDistance = 0.0f;
	float CameraLagMaxTimeStep = 0.0f;
	float CameraLagSpeed = 0.0f;
	float CameraRotationLagSpeed = 0.0f;
	//FVector TargetOffset;
	float TargetArmLength = 100.0f;
	//FVector UnfixedCameraPosition;
	//FVector SocketOffset;
	//FVector TargetOffset;
	//FVector PreviousDesiredLoc;
	//FVector PreviousArmOrigin;
	//FRotator PreviousDesiredRot;

public:
	//FRotator GetDesiredRotation();
	//FRotator GetTargetRotation();
public:
	//USpringArmComponent(const FObjectInitializer& ObjectInitializer)
public:
	void UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime);
};

