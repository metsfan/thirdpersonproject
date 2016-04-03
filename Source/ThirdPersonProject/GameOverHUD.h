// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameOverHUD.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;
class AMyPlayerState;

enum UGameOverState {
	PlayerDead,
	GameOver,
	ReadyCheck
};

UCLASS()
class THIRDPERSONPROJECT_API UGameOverHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void OnPlayerReadyToRestart(AMyPlayerState* player);

	UPROPERTY(BlueprintReadWrite)
	UButton* RestartButtonWidget;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* GameOverTextWidget;
};
