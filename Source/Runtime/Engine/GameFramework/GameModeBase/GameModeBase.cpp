#include "GameModeBase.h"

AGameModeBase::AGameModeBase()
{
	bPauseable = true;
	bIsPaused = false;
	defaultPawnClass = TSubclassOf<APawn>();
	//defaultPawn = TObjectPtr<APawn>();
	hudClass = TSubclassOf<AHUD>();
	playerControllerClass = TSubclassOf<APlayerController>();
	gameStateClass = TSubclassOf<AGameStateBase>();
	//gameState = TObjectPtr<AGameStateBase>();
	gameSessionClass = TSubclassOf<AGameSession>();
	//gameSession = TObjectPtr<AGameSession>();
}

bool AGameModeBase::AllowPausing(APlayerController* _playerController)
{
	// TODO CHECK LE PAUSEABLE DU PLAYER CONTROLLER

	return bPauseable;
}

void AGameModeBase::InitializeHUDForPlayer(APlayerController* NewPlayer)
{
	//TODO PASSER AU NEW PLAYER LE TSUBCLASSOF DE L'HUD 

}

void AGameModeBase::ChangeName(AController* Controller, const FString& NewName, bool bNameChange)
{
	// Controller->SetName(NewName);
	// return bNameChange;
}

void AGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	// TODO LOAD LA MAP ET LES OPTIONS QUELQUE PART :D
}

void AGameModeBase::StartPlay()
{
	// YES
}

AActor* AGameModeBase::ChoosePlayerStart(AController* Player)
{
	// TODO RETOURNER UNE POSITION DANS UN ESPACE INNOCUPE
	return nullptr;
}

AActor* AGameModeBase::FindPlayerStart(AController* Player, const FString& IncomingName)
{
	// TODO PARCOURIR LE LEVEL ? POUR TROUVER DES PLAYER STATS SINON APPEL CHOOSE PLAYER START
	return ChoosePlayerStart(Player);
}

void AGameModeBase::RestartPlayer(AController* NewPlayer)
{
	AActor* _actor = FindPlayerStart(NewPlayer, "Player");

	if (!_actor)
		return;

	// TODO SPAWN LE PLAYER
}

void AGameModeBase::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	// TODO CHECK LE LEVEL ? POUR VOIR SI StartSpot EST INNOCUPEE ET SPAWN NewPlayer
}

UClass* AGameModeBase::GetDefaultPawnClassForController(AController* InController)
{
	// TODO RETURN LA CLASSE DE BASE DU CONTROLLER InController->BaseClass() ?
	return nullptr;
}

void AGameModeBase::SetPlayerDefaults(APawn* PlayerPawn)
{
	// TODO RestartPlayer(PlayerPawn->GetController());
}

APlayerController* AGameModeBase::SpawnPlayerControllerCommon(FVector const& SpawnLocation, FRotator const& SpawnRotation, TSubclassOf<APlayerController> InPlayerControllerClass)
{
	// TODO SPAWN LE PLAYER DEPUIS LE InPlayerControllerClass ET LUI SET SA LOCATION ET ROTATION PUIS LE RETURN 
	return nullptr;
}
