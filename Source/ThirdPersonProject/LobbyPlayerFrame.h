// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "LobbyPlayerFrame.generated.h"

/**
 * 
 */
class AMainPlayerController;

UCLASS()
class THIRDPERSONPROJECT_API ULobbyPlayerFrame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	AMainPlayerController* Player;
};
