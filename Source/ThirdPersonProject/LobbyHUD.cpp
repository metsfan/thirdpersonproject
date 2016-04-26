// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainGameState.h"
#include "MainMenuGameMode.h"
#include "MainPlayerController.h"
#include "LobbyHUD.h"
#include "Components/VerticalBox.h"
#include "MainMenuGameState.h"
#include "LobbyPlayerFrame.h"

static ConstructorHelpers::FClassFinder<ULobbyPlayerFrame> *LobbyPlayerFrameBPClass = NULL;

ULobbyHUD::ULobbyHUD(const FObjectInitializer& ObjectInitializer): 
	Super(ObjectInitializer)
{
	if (!LobbyPlayerFrameBPClass) {
		LobbyPlayerFrameBPClass = new ConstructorHelpers::FClassFinder<ULobbyPlayerFrame>(TEXT("/Game/BP_LobbyPlayerFrame"));
	}
}

void ULobbyHUD::OnNicknameSubmitButtonClick()
{
	NicknamePopupEntryWidget->SetVisibility(ESlateVisibility::Collapsed);

	const FString& nickNameText = NicknameEntryTextBox->GetText().ToString();

	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	pc->SetNickname(nickNameText);
}

void ULobbyHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void ULobbyHUD::OnPlayerJoinedLobby(const TArray<AMyPlayerState*>& players)
{
	auto gameState = Cast<AMainMenuGameState>(GetWorld()->GetGameState());

	auto addPlayer = [this](AMyPlayerState* player) {
		auto widget = CreateWidget<ULobbyPlayerFrame>(GetWorld(), LobbyPlayerFrameBPClass->Class);
		widget->Player = player;
		ConnectedPlayersWidget->AddChildToVerticalBox(widget);
	};

	ConnectedPlayersWidget->ClearChildren();

	for (auto& player : players) {
		if (player->PlayerId > 0) {
			auto myPlayer = Cast<AMyPlayerState>(player);
			UE_LOG(MyLog, Log, TEXT("Player name: %s"), *myPlayer->Name);

			addPlayer(myPlayer);
		}
	}
}