// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "MyPlayerState.h"
#include "PlayerFrame.generated.h"

/**
 * 
 */

class AThirdPersonProjectCharacter;

UCLASS()
class THIRDPERSONPROJECT_API UPlayerFrame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		AMyPlayerState* Player;
	
};
