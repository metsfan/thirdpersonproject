// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainPlayerController.h"
#include "ThirdPersonProjectCharacter.h"
#include "ActionEvent.h"
#include "MyPlayerState.h"

AMainPlayerController::AMainPlayerController(): Super(),
	mUniqueID(FGuid::NewGuid())
{
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	this->InitPlayerState();

	
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//InputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &AMainPlayerController::OnLeftMouseButtonPressed);
	//InputComponent->BindAction("LeftMouseButton", IE_Released, this, &AMainPlayerController::OnLeftMouseButtonReleased);

	//auto inputManager = UInputEventManager::Get();
	//inputManager->Setup(InputComponent);

	
}

void AMainPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto Player = Cast<ABaseCharacter>(InPawn);
	auto PlayerState = Cast<AMyPlayerState>(this->PlayerState);
	if (Player && PlayerState) {
		if (!Nickname.IsEmpty()) {
			Player->Name = Nickname;
		}

		PlayerState->Health = Player->Health;
		PlayerState->MaxHealth = Player->MaxHealth;
		PlayerState->Name = Player->Name;
	}
}

void AMainPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	auto PlayerState = Cast<AMyPlayerState>(this->PlayerState);
	/*if (PlayerState) {
		
	}*/
	auto Player = Cast<ABaseCharacter>(GetPawn());

	if (Player && this->PlayerState) {
		if (HasAuthority()) {
			//Player->AddHealth(-100);
			PlayerState->Health = Player->Health;
		}
		else
		{
			Player->Health = PlayerState->Health;
		}
		
		//
		//Player->MaxHealth = PlayerState->MaxHealth;
	}
}
