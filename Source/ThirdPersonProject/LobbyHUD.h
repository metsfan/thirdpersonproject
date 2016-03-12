// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "LobbyHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API ULobbyHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnNicknameSubmitButtonClick();

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* NicknameEntryTextBox;
	
};
