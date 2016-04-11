// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "LobbyHUD.generated.h"

/**
 * 
 */
class AMainPlayerController;
class UVerticalBox;

UCLASS()
class THIRDPERSONPROJECT_API ULobbyHUD : public UUserWidget
{
	GENERATED_BODY()

	ULobbyHUD(const FObjectInitializer& ObjectInitializer);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION()
	void OnPlayerJoinedLobby(const TArray<AMyPlayerState*>& players);

protected:
	UFUNCTION(BlueprintCallable, Category = "Events")
	void OnNicknameSubmitButtonClick();

	UPROPERTY(BlueprintReadWrite)
	UEditableTextBox* NicknameEntryTextBox;

	UPROPERTY(BlueprintReadWrite)
	UVerticalBox* NicknamePopupEntryWidget;
	
	UPROPERTY(BlueprintReadWrite)
	UVerticalBox* ConnectedPlayersWidget;
};
