// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainPlayerController.h"
#include "ThirdPersonProjectCharacter.h"
#include "ActionEvent.h"
#include "MyPlayerState.h"
#include "MainMenuGameMode.h"
#include "LobbyHUD.h"
#include "GameHUD.h"
#include "MainMenuGameState.h"
#include "UnrealNetwork.h"

AMainPlayerController::AMainPlayerController(): Super()
{
	bReplicates = true;
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

void AMainPlayerController::InitPlayerState()
{
	Super::InitPlayerState();

	if (Role == ROLE_AutonomousProxy) {
		
	}
}

void AMainPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

}

void AMainPlayerController::OnPlayerDied(AThirdPersonProjectCharacter* Character)
{
	PlayerHUD->GameOverHUDWidget->SetVisibility(ESlateVisibility::Visible);
}

void AMainPlayerController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	auto Player = Cast<ABaseCharacter>(this->GetPawn());
	auto PlayerState = Cast<AMyPlayerState>(this->PlayerState);
	if (PlayerState) {
		if (PlayerHUD != NULL && PlayerHUD->PlayerFrameWidget->Player == NULL) {
			PlayerHUD->PlayerFrameWidget->Player = Cast<AMyPlayerState>(this->PlayerState);
		}

		PlayerState->Update(Player);
	}
}

bool AMainPlayerController::SetNickname_Validate(const FString& newNickname)
{
	return newNickname.Len() > 0;
}

void AMainPlayerController::SetNickname_Implementation(const FString& newNickname)
{
	this->Nickname = newNickname;

	auto gameState = Cast<AMainMenuGameState>(GetWorld()->GetGameState());
	gameState->JoinedPlayers.Add(this);

	auto gameMode = Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode());
	this->NotifyPlayerJoinedLobby();
}

void AMainPlayerController::NotifyPlayerJoinedLobby_Implementation()
{
	
}

void AMainPlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerController, Nickname);
	DOREPLIFETIME(AMainPlayerController, Ready);
}

void AMainPlayerController::OnRep_Nickname()
{ 
	if (LobbyHUDWidget) {
		auto gameState = Cast<AMainMenuGameState>(GetWorld()->GetGameState());
		gameState->JoinedPlayers.Add(this);

		LobbyHUDWidget->OnPlayerJoinedLobby(this);
	}
}

bool AMainPlayerController::Server_NotifyReady_Validate(bool Ready)
{
	return true;
}

void AMainPlayerController::Server_NotifyReady_Implementation(bool pReady)
{
	this->Ready = pReady;

	auto gameMode = Cast<AMainMenuGameMode>(GetWorld()->GetAuthGameMode());
	gameMode->CheckIfGameReady();
}