// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonProject.h"
#include "ThirdPersonProjectGameMode.h"
#include "ThirdPersonProjectCharacter.h"
#include "GameFramework/HUD.h"
#include "MainPlayerController.h"
#include "MainGameState.h"
#include "MyPlayerState.h"
#include "EngineUtils.h"
#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

static const float kSpawnTimerInterval = 5.0f;

static ConstructorHelpers::FClassFinder<ACharacter> *MeleeEnemyBPClass = NULL;
static ConstructorHelpers::FClassFinder<ACharacter> *RangedEnemyBPClass = NULL;

AThirdPersonProjectGameMode::AThirdPersonProjectGameMode() :
	AGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	if (!MeleeEnemyBPClass) {
		MeleeEnemyBPClass = new ConstructorHelpers::FClassFinder<ACharacter>(TEXT("/Game/BP_MeleeEnemy"));
	}

	if (!RangedEnemyBPClass) {
		RangedEnemyBPClass = new ConstructorHelpers::FClassFinder<ACharacter>(TEXT("/Game/BP_RangedEnemy"));
	}

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = AMainPlayerController::StaticClass();
	}

	GameStateClass = AMainGameState::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();
}

AThirdPersonProjectGameMode::~AThirdPersonProjectGameMode()
{
	if (GetWorld()) {
		GetWorldTimerManager().ClearTimer(SpawnTimer);
	}
}

void AThirdPersonProjectGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

}

void AThirdPersonProjectGameMode::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto playerController = Cast<AMainPlayerController>(NewPlayer);
	auto playerState = Cast<AMyPlayerState>(NewPlayer->PlayerState);

	auto gameState = this->GetGameState<AMainGameState>();
	if (playerState) {
		playerState->NetID = playerController->NetID;
		gameState->ConnectedPlayersArray.Add(playerState);
	}
	//gameState->OnPlayerJoined(playerState);
}

void AThirdPersonProjectGameMode::StartPlay()
{
	Super::StartPlay();

	auto gameState = this->GetGameState<AMainGameState>();
	gameState->GameStartCountdown = 5;

	GetWorldTimerManager().SetTimer(GameStartTimer, this, &AThirdPersonProjectGameMode::GameStartTimerCallback, 1.0, true, 1.0);
}

void AThirdPersonProjectGameMode::GameStartTimerCallback() 
{
	auto gameState = this->GetGameState<AMainGameState>();
	gameState->GameStartCountdown -= 1;

	if (gameState->GameStartCountdown == 0) {
		this->UpdateSpawnPoints();
		//this->BeginSpawningEnemies();
	}
	else if (gameState->GameStartCountdown < 0) {
		GetWorldTimerManager().ClearTimer(GameStartTimer);
	}
}

void AThirdPersonProjectGameMode::StartMatch()
{
	Super::StartMatch();
}

void AThirdPersonProjectGameMode::EndMatch()
{
	Super::EndMatch();

	GetWorldTimerManager().ClearTimer(SpawnTimer);
}

void AThirdPersonProjectGameMode::UpdateSpawnPoints()
{
	SpawnPoints.Empty();

	for(TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SpawnPoints.Add(*ActorItr);
	}
}

void AThirdPersonProjectGameMode::BeginSpawningEnemies()
{
	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this] {
		this->SpawnEnemies();
	});

	GetWorldTimerManager().SetTimer(SpawnTimer, TimerCallback, kSpawnTimerInterval, true, 0.0);
}

void AThirdPersonProjectGameMode::SpawnEnemies()
{
	auto spawnPoint = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];
	if (spawnPoint) {
		auto spawnLocation = spawnPoint->GetActorLocation();

		int numSpawns = FMath::RandRange(2, 6);

		for (int i = 0; i < numSpawns; i++) {
			auto staggeredLocation = spawnLocation + FVector(i * 10, 0, 0);
			auto transform = FTransform(staggeredLocation);

			if (i % 2 == 0) {
				UAIBlueprintHelperLibrary::SpawnAIFromClass(this, MeleeEnemyBPClass->Class, NULL, staggeredLocation);
			}
			else {
				UAIBlueprintHelperLibrary::SpawnAIFromClass(this, RangedEnemyBPClass->Class, NULL, staggeredLocation);
			}
			//actor->AIControllerClass = NewObject<AController>(GetLevel(), GenericEnemyAIControllerBPClass->Class);
		}
	}
}

void AThirdPersonProjectGameMode::RestartGameIfAllReady()
{
	auto gameState = Cast<AMainGameState>(this->GameState);

	if (gameState->GetConnectedPlayers().Num() > 0) {
		bool allReady = true;

		for (auto player : gameState->GetConnectedPlayers()) {
			allReady &= player.Value->ReadyToRestart;
		}

		if (allReady) {
			GetWorldTimerManager().ClearTimer(SpawnTimer);
			GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap", true);
		}
	}
}
