#pragma once
#include "../../../Objects/Actors/AActor.h"
#include "../../../../Editor/Pointers/TSubclassOf.h"
#include "../../../../Editor/Pointers/TObjectPtr.h"


class APawn;
class AHUD;
class APlayerController;
class AController;
class AGameStateBase;
class AGameSession;
class FRotator;

class AGameModeBase : public AActor
{
	bool bPauseable;
	bool bIsPaused;
	FString defaultPlayerName;
	TSubclassOf<APawn> defaultPawnClass;
	//TObjectPtr<APawn> defaultPawn;
	TSubclassOf<AHUD> hudClass;
	TSubclassOf<APlayerController> playerControllerClass;

	TSubclassOf<AGameStateBase> gameStateClass;
	//TObjectPtr<AGameStateBase> gameState;

	TSubclassOf<AGameSession> gameSessionClass;
	//TObjectPtr<AGameSession> gameSession;

public:
	AGameModeBase();

	FString GetDefaultPlayerName() const { return defaultPlayerName; }
	//TObjectPtr<APawn> GetDefaultPawn() const { return defaultPawn; }
	TSubclassOf<AHUD> GetHUDClass() const { return hudClass; }
	TSubclassOf<APlayerController> GetPlayerControllerClass() const { return playerControllerClass; }
	//TObjectPtr<AGameStateBase> GetGameState() const { return gameState; }
	//TObjectPtr<AGameSession> GetGameSession() const { return gameSession; }
	bool GetIsPaused() const { return bIsPaused;}
	bool GetIsPauseable() const { return bPauseable;}

	//void  SetPlayerDefaults(APawn* PlayerPawn) { defaultPawn = PlayerPawn; }

public:
	bool AllowPausing(APlayerController* _playerController);
	void  InitializeHUDForPlayer(APlayerController* NewPlayer);
	void  ChangeName(AController* Controller, const FString& NewName, bool bNameChange);
	void  InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage);
	void  StartPlay();
	AActor* ChoosePlayerStart(AController* Player);
	AActor* FindPlayerStart(AController* Player, const FString& IncomingName);
	void  RestartPlayer(AController* NewPlayer);
	void  RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot);
	UClass* GetDefaultPawnClassForController(AController* InController);
	void SetPlayerDefaults(APawn* PlayerPawn);
	APlayerController* SpawnPlayerControllerCommon(FVector const& SpawnLocation, FRotator const& SpawnRotation, TSubclassOf<APlayerController> InPlayerControllerClass);
};