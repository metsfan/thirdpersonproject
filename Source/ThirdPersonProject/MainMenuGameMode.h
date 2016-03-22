// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */

class AMainPlayerController;

UCLASS()
class THIRDPERSONPROJECT_API AMainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	void CheckIfGameReady();
};
