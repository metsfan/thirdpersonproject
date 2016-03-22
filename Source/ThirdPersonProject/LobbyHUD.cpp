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

void ULobbyHUD::OnPlayerJoinedLobby(AMainPlayerController* player)
{
	auto gameState = Cast<AMainMenuGameState>(GetWorld()->GetGameState());
	auto connectedPlayers = gameState->JoinedPlayers;

	//ConnectedPlayersWidget->ClearChildren();

	//for (auto& connectedPlayer : connectedPlayers) {
		UE_LOG(MyLog, Log, TEXT("Player name: %s"), *player->Nickname);

	auto widget = CreateWidget<ULobbyPlayerFrame>(GetWorld(), LobbyPlayerFrameBPClass->Class);
	widget->Player = player;
	ConnectedPlayersWidget->AddChildToVerticalBox(widget);
	//}
}