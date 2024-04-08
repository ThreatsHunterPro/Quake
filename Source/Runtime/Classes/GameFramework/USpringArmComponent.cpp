#include "USpringArmComponent.h"

//USpringArmComponent::USpringArmComponent(const FObjectInitializer& ObjectInitializer)
//{
// 	PrimaryComponentTick.bCanEverTick = true;
	//PrimaryComponentTick.TickGroup = TG_PostPhysics;

	//bAutoActivate = true;
	//bTickInEditor = true;
	//bUsePawnControlRotation = false;
	//bDoCollisionTest = true;

	//bInheritPitch = true;
	//bInheritYaw = true;
	//bInheritRoll = true;

	//TargetArmLength = 300.0f;

	//RelativeSocketRotation = FQuat::Identity;

	//bUseCameraLagSubstepping = true;
	//CameraLagSpeed = 10.f;
	//CameraRotationLagSpeed = 10.f;
	//CameraLagMaxTimeStep = 1.f / 60.f;
	//CameraLagMaxDistance = 0.f;
	//bClampToMaxPhysicsDeltaTime = false;

	//UnfixedCameraPosition = FVector::ZeroVector;
//}


//FRotator USpringArmComponent::GetDesiredRotation() const
//{
//	return GetComponentRotation();
//}


//FRotator USpringArmComponent::GetTargetRotation() const
//{
//	FRotator DesiredRot = GetDesiredRotation();
//
//	if (bUsePawnControlRotation)
//	{
//		if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
//		{
//			const FRotator PawnViewRotation = OwningPawn->GetViewRotation();
//			if (DesiredRot != PawnViewRotation)
//			{
//				DesiredRot = PawnViewRotation;
//			}
//		}
//	}
//
//	// If inheriting rotation, check options for which components to inherit
//	if (!IsUsingAbsoluteRotation())
//	{
//		const FRotator LocalRelativeRotation = GetRelativeRotation();
//		if (!bInheritPitch)
//		{
//			DesiredRot.Pitch = LocalRelativeRotation.Pitch;
//		}
//
//		if (!bInheritYaw)
//		{
//			DesiredRot.Yaw = LocalRelativeRotation.Yaw;
//		}
//
//		if (!bInheritRoll)
//		{
//			DesiredRot.Roll = LocalRelativeRotation.Roll;
//		}
//	}
//
//	return DesiredRot;
//}

void USpringArmComponent::UpdateDesiredArmLocation(bool bDoTrace, bool bDoLocationLag, bool bDoRotationLag, float DeltaTime)
{
	//FRotator DesiredRot = GetTargetRotation();

	// Apply 'lag' to rotation if desired
	//if (bDoRotationLag)
	//{
	//	if (bUseCameraLagSubstepping && DeltaTime > CameraLagMaxTimeStep && CameraRotationLagSpeed > 0.f)
	//	{
	//		const FRotator ArmRotStep = (DesiredRot - PreviousDesiredRot).GetNormalized() * (1.f / DeltaTime);
	//		FRotator LerpTarget = PreviousDesiredRot;
	//		float RemainingTime = DeltaTime;
	//		while (RemainingTime > UE_KINDA_SMALL_NUMBER)
	//		{
	//			const float LerpAmount = FMath::Min(CameraLagMaxTimeStep, RemainingTime);
	//			LerpTarget += ArmRotStep * LerpAmount;
	//			RemainingTime -= LerpAmount;

	//			DesiredRot = FRotator(FMath::QInterpTo(FQuat(PreviousDesiredRot), FQuat(LerpTarget), LerpAmount, CameraRotationLagSpeed));
	//			PreviousDesiredRot = DesiredRot;
	//		}
	//	}
	//	else
	//	{
	//		DesiredRot = FRotator(FMath::QInterpTo(FQuat(PreviousDesiredRot), FQuat(DesiredRot), DeltaTime, CameraRotationLagSpeed));
	//	}
	//}
	//PreviousDesiredRot = DesiredRot;

	//TODO GetComponentLocation() in component;
	//FVector ArmOrigin = GetComponentLocation() + TargetOffset;

	//FVector DesiredLoc = ArmOrigin;
	//if (bDoLocationLag)
	//{
	//	if (bUseCameraLagSubstepping && DeltaTime > CameraLagMaxTimeStep && CameraLagSpeed > 0.f)
	//	{
	//		const FVector ArmMovementStep = (DesiredLoc - PreviousDesiredLoc) * (1.f / DeltaTime);
	//		FVector LerpTarget = PreviousDesiredLoc;

	//		float RemainingTime = DeltaTime;
	//		while (RemainingTime > UE_KINDA_SMALL_NUMBER)
	//		{
	//			const float LerpAmount = FMath::Min(CameraLagMaxTimeStep, RemainingTime);
	//			LerpTarget += ArmMovementStep * LerpAmount;
	//			RemainingTime -= LerpAmount;

	//			DesiredLoc = FMath::VInterpTo(PreviousDesiredLoc, LerpTarget, LerpAmount, CameraLagSpeed);
	//			PreviousDesiredLoc = DesiredLoc;
	//		}
	//	}
	//	else
	//	{
	//		DesiredLoc = FMath::VInterpTo(PreviousDesiredLoc, DesiredLoc, DeltaTime, CameraLagSpeed);
	//	}

		// Clamp distance if requested
		//bool bClampedDist = false;
		//if (CameraLagMaxDistance > 0.f)
		//{
		//	const FVector FromOrigin = DesiredLoc - ArmOrigin;
		//	if (FromOrigin.SizeSquared() > FMath::Square(CameraLagMaxDistance))
		//	{
		//		DesiredLoc = ArmOrigin + FromOrigin.GetClampedToMaxSize(CameraLagMaxDistance);
		//		bClampedDist = true;
		//	}
		//}
	//}

	//PreviousArmOrigin = ArmOrigin;
	//PreviousDesiredLoc = DesiredLoc;

	//DesiredLoc -= DesiredRot.Vector() * TargetArmLength;
	//DesiredLoc += FRotationMatrix(DesiredRot).TransformVector(SocketOffset);

	//FVector ResultLoc;
	//if (bDoTrace && (TargetArmLength != 0.0f))
	//{
	//	bIsCameraFixed = true;
	//	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(SpringArm), false, GetOwner());

	//	FHitResult Result;
	//	GetWorld()->SweepSingleByChannel(Result, ArmOrigin, DesiredLoc, FQuat::Identity, ProbeChannel, FCollisionShape::MakeSphere(ProbeSize), QueryParams);

	//	UnfixedCameraPosition = DesiredLoc;

	//	ResultLoc = BlendLocations(DesiredLoc, Result.Location, Result.bBlockingHit, DeltaTime);

	//	if (ResultLoc == DesiredLoc)
	//	{
	//		bIsCameraFixed = false;
	//	}
	//}
	//else
	//{
	//	ResultLoc = DesiredLoc;
	//	bIsCameraFixed = false;
	//	UnfixedCameraPosition = ResultLoc;
	//}

	//FTransform WorldCamTM(DesiredRot, ResultLoc);
	//FTransform RelCamTM = WorldCamTM.GetRelativeTransform(GetComponentTransform());

	//RelativeSocketLocation = RelCamTM.GetLocation();
	//RelativeSocketRotation = RelCamTM.GetRotation();


//Component
	//UpdateChildTransforms();
}
