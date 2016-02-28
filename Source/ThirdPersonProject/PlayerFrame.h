// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "ThirdPersonProjectCharacter.h"
#include "PlayerFrame.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UPlayerFrame : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	AThirdPersonProjectCharacter* Player;
	
};
