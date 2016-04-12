// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ThirdPersonProjectCharacter.h"
#include "GameHUD.h"
#include "MainGameState.h"
#include "MainPlayerController.h"
#include "MyPlayerState.h"
#include "PlayerFrame.h"
#include "MainGameState.h"
#include "WidgetHelper.h"
#include "Components/CanvasPanelSlot.h"

static ConstructorHelpers::FClassFinder<UPlayerFrame> *PlayerFrameBPClass = NULL;

UGameHUD::UGameHUD(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	if (!PlayerFrameBPClass) {
		PlayerFrameBPClass = new ConstructorHelpers::FClassFinder<UPlayerFrame>(TEXT("/Game/BP_PlayerFrame"));
	}
}

void UGameHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GameOverHUDWidget->UpdateState();
}

void UGameHUD::NativeConstruct()
{
	Super::NativeConstruct();

	GameOverHUDWidget->OnRestartClick.AddDynamic(this, &UGameHUD::OnRestartClick_Private);
}

void UGameHUD::OnRestartClick_Private()
{
	//this->GameOverHUDWidget->SetState(UGameOverState::Ready);

	OnRestartClick.Broadcast();
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

void UGameHUD::SetPlayer(AMyPlayerState* pPlayer)
{
	Player = pPlayer;

	PlayerFrameWidget->Player = pPlayer;
}

void UGameHUD::SetScoreVisible(bool visible)
{
	ScorePanelWidget->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

void UGameHUD::OnPlayerDied()
{
	//GameOverHUDWidget->SetState(UGameOverState::PlayerDead);
}

void UGameHUD::OnGameOver()
{
	//GameOverHUDWidget->SetState(UGameOverState::ReadyCheck);
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

void UGameHUD::UpdatePartyFrame()
{
	auto gameState = this->GetWorld()->GetGameState<AMainGameState>();
	if (gameState && PlayerFrameWidget->Player) {
		auto players = gameState->PlayerArray;

		PartyPanelWidget->ClearChildren();

		for (auto player : players) {
			auto myPlayer = Cast<AMyPlayerState>(player);
			if (myPlayer->PlayerId > 0 && player->PlayerId != PlayerFrameWidget->Player->PlayerId) {
				auto widget = CreateWidget<UPlayerFrame>(GetWorld()->GetGameInstance(), PlayerFrameBPClass->Class);
				widget->Player = myPlayer;
				PartyPanelWidget->AddChildToVerticalBox(widget);
			}
		}
	}
}

FVector2D UGameHUD::GetCrosshairPosition()
{
	auto canvasSlot = Cast<UCanvasPanelSlot>(CrosshairWidget->Slot);
	return FWidgetHelper::GetAbsolutePositionForCanvasSlot(this, canvasSlot);
}


