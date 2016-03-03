// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "HealthFrame.generated.h"

/**
 * 
 */
class ABaseCharacter;

UCLASS()
class THIRDPERSONPROJECT_API UHealthFrame : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	
	UPROPERTY(BlueprintReadWrite)
		ABaseCharacter* Character;
	
};
