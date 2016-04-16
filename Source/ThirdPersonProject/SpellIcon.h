// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "ThirdPersonProjectCharacter.h"
#include "SpellData.h"
#include "SpellIcon.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API USpellIcon : public UUserWidget
{
	GENERATED_BODY()
	
	
	
public:
	UPROPERTY(BlueprintReadWrite)
		UTextBlock* HotkeyWidget;

	UPROPERTY(BlueprintReadWrite)
		UImage* IconWidget;

	UPROPERTY(BlueprintReadOnly)
		USpellData* Spell;
};
