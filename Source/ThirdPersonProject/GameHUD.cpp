// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "ThirdPersonProjectCharacter.h"
#include "GameHUD.h"
#include "MainGameState.h"
#include "MyPlayerState.h"

void UGameHUD::NativeConstruct()
{
	Super::Construct();
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

