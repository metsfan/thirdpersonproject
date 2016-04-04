// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerFrame.h"
#include "GameOverHUD.h"
#include "Components/VerticalBox.h"
#include "GameHUD.generated.h"

/**
 * 
 */

class AMyPlayerState;

UCLASS()
class THIRDPERSONPROJECT_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

	UGameHUD(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdatePartyFrame();

private:
	UFUNCTION()
	void OnRestartClick_Private();

protected:
	UFUNCTION(BlueprintCallable, Category=Functions)
	FText GetCountdownTimerText();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestartClickSignature);
	FRestartClickSignature OnRestartClick;

	void OnLocalPlayerJoined(AMyPlayerState* player);
	void OnRemotePlayerJoined(AMyPlayerState* player);
	void OnPlayerDied();
	void OnGameOver();
	void OnPlayerReadyToRestart(AMyPlayerState* player);

	UPROPERTY(BlueprintReadWrite)
	UPlayerFrame* PlayerFrameWidget;

	UPROPERTY(BlueprintReadWrite)
	UGameOverHUD* GameOverHUDWidget;
	
	UPROPERTY(BlueprintReadWrite)
	UVerticalBox* PartyPanelWidget;
};
