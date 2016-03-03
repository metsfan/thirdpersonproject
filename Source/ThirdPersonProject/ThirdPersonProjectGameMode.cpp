// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonProject.h"
#include "ThirdPersonProjectGameMode.h"
#include "ThirdPersonProjectCharacter.h"
#include "GameFramework/HUD.h"
#include "MainPlayerController.h"
#include "EngineUtils.h"

static const float kSpawnTimerInterval = 5.0;

static ConstructorHelpers::FClassFinder<AActor> *GenericEnemyBPClass = NULL;

AThirdPersonProjectGameMode::AThirdPersonProjectGameMode() :
	AGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));

	if (!GenericEnemyBPClass) {
		GenericEnemyBPClass = new ConstructorHelpers::FClassFinder<AActor>(TEXT("/Game/BP_GenericEnemy"));
	}

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		PlayerControllerClass = AMainPlayerController::StaticClass();
	}
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

	GetWorldTimerManager().SetTimer(SpawnTimer, TimerCallback, kSpawnTimerInterval, true, 0.0);
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

	int numSpawns = FMath::RandRange(1, 5);

	for (int i = 0; i < numSpawns; i++) {
		auto staggeredLocation = spawnLocation + (FMath::VRand() * FMath::FRandRange(5, 10));
		auto transform = FTransform(staggeredLocation);

		GetWorld()->SpawnActor(GenericEnemyBPClass->Class, &transform);
	}
}
