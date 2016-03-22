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

static ConstructorHelpers::FClassFinder<ACharacter> *GenericEnemyBPClass = NULL;
static ConstructorHelpers::FClassFinder<AAIController> *GenericEnemyAIControllerBPClass = NULL;

AThirdPersonProjectGameMode::AThirdPersonProjectGameMode() :
	AGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	if (!GenericEnemyBPClass) {
		GenericEnemyBPClass = new ConstructorHelpers::FClassFinder<ACharacter>(TEXT("/Game/BP_GenericEnemy"));
	}

	if (!GenericEnemyAIControllerBPClass) {
		GenericEnemyAIControllerBPClass = new ConstructorHelpers::FClassFinder<AAIController>(TEXT("/Game/GenericEnemyAIController"));
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

void AThirdPersonProjectGameMode::BeginPlay()
{
	Super::BeginPlay();

	this->UpdateSpawnPoints();

	FTimerDelegate TimerCallback;
	TimerCallback.BindLambda([this] {
		this->SpawnEnemies();
	});

	GetWorldTimerManager().SetTimer(SpawnTimer, TimerCallback, kSpawnTimerInterval, true, 1.0);
}

void AThirdPersonProjectGameMode::UpdateSpawnPoints()
{
	for(TActorIterator<ASpawnPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		SpawnPoints.Add(*ActorItr);
	}
}

void AThirdPersonProjectGameMode::SpawnEnemies()
{
	auto spawnPoint = SpawnPoints[FMath::RandRange(0, SpawnPoints.Num() - 1)];
	auto spawnLocation = spawnPoint->GetActorLocation();

	int numSpawns = FMath::RandRange(1, 3);

	for (int i = 0; i < numSpawns; i++) {
		auto staggeredLocation = spawnLocation + FVector(i * 10, 0, 0);
		auto transform = FTransform(staggeredLocation);

		auto actor = UAIBlueprintHelperLibrary::SpawnAIFromClass(this, GenericEnemyBPClass->Class, NULL, staggeredLocation);
		//actor->AIControllerClass = NewObject<AController>(GetLevel(), GenericEnemyAIControllerBPClass->Class);
	}
}
