// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ThirdPersonProjectCharacter.h"
#include "GameHUD.h"
#include "MainGameState.h"
#include "MainPlayerController.h"
#include "MyPlayerState.h"
#include "PlayerFrame.h"
#include "MainGameState.h"

static ConstructorHelpers::FClassFinder<UPlayerFrame> *PlayerFrameBPClass = NULL;

UGameHUD::UGameHUD(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	if (!PlayerFrameBPClass) {
		PlayerFrameBPClass = new ConstructorHelpers::FClassFinder<UPlayerFrame>(TEXT("/Game/BP_PlayerFrame"));
	}
}

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

FText UGameHUD::GetCountdownTimerText()
{
	auto gameState = this->GetWorld()->GetGameState<AMainGameState>();
	if (gameState) {
		if (gameState->GameStartCountdown > 0) {
			return FText::AsNumber(gameState->GameStartCountdown);
		}
		else if (gameState->GameStartCountdown == 0) {
			return FText::FromString(FString("Start!"));
		}
	}

	return FText::FromString("");
}

void UGameHUD::OnPlayerDied()
{
	GameOverHUDWidget->SetVisibility(ESlateVisibility::Visible);
}

void UGameHUD::OnLocalPlayerJoined(AMyPlayerState* player)
{
	PlayerFrameWidget->Player = player;

	this->UpdatePartyFrame();
}

void UGameHUD::OnRemotePlayerJoined(AMyPlayerState* player)
{
	this->UpdatePartyFrame();
}

void UGameHUD::OnPlayerReadyToRestart(AMyPlayerState* player)
{
	GameOverHUDWidget->OnPlayerReadyToRestart(player);
}

void UGameHUD::UpdatePartyFrame()
{
	auto gameState = this->GetWorld()->GetGameState<AMainGameState>();
	if (gameState && PlayerFrameWidget->Player) {
		auto players = gameState->PlayerArray;
		for (auto player : gameState->ConnectedPlayers) {
			if (player.Value->PlayerId != PlayerFrameWidget->Player->PlayerId) {
				auto widget = CreateWidget<UPlayerFrame>(GetWorld()->GetGameInstance(), PlayerFrameBPClass->Class);
				widget->Player = player.Value;
				PartyPanelWidget->AddChildToVerticalBox(widget);
			}
		}
	}
}


