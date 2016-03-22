// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "MainGameState.h"
#include "LobbyHUD.h"

void ULobbyHUD::OnNicknameSubmitButtonClick()
{
	const FString& nickNameText = NicknameEntryTextBox->GetText().ToString();

	auto gameState = Cast<AMainGameState>(GetWorld()->GameState);
	auto pc = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
	//gameState->ServerSetPlayerName(pc->GetUniqueID(), nickNameText);
}