// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerFrame.h"
#include "GameOverHUD.h"
#include "Components/VerticalBox.h"
#include "Components/Image.h"
#include "SpellIcon.h"
#include "ThirdPersonProjectCharacter.h"
#include "GameHUD.generated.h"

/**
 * 
 */

class AMyPlayerState;
class UScoreOverlay;

UCLASS()
class THIRDPERSONPROJECT_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

	UGameHUD(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


protected:
	UPROPERTY(BlueprintReadWrite)
	AMyPlayerState* Player;

private:
	UFUNCTION()
	void OnRestartClick_Private();

	TArray<AMyPlayerState*> ConnectedPlayers;

	TMap<FSpellAction, USpellIcon*> SpellIconWidgets;

public:
	UFUNCTION(BlueprintCallable, Category = TextBinding)
	FText GetCountdownTimerText();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestartClickSignature);
	FRestartClickSignature OnRestartClick;

	void SetPlayer(AMyPlayerState* pPlayer);
	AMyPlayerState* GetPlayer() { return Player; }

	void UpdatePartyFrame();

	void SetScoreVisible(bool visible);

	void OnLocalPlayerJoined(AMyPlayerState* player);
	void OnRemotePlayerJoined(AMyPlayerState* player);
	void OnPlayerDied();
	void OnGameOver();
	void OnPlayerReadyToRestart(AMyPlayerState* player);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetSpellIconWidget(FSpellAction Action, USpellIcon* Widget);

	void SetSpellData(FSpellAction Action, USpellData* Data);

	FVector2D GetCrosshairPosition();

	UPROPERTY(BlueprintReadWrite)
	UPlayerFrame* PlayerFrameWidget;

	UPROPERTY(BlueprintReadWrite)
	UGameOverHUD* GameOverHUDWidget;
	
	UPROPERTY(BlueprintReadWrite)
	UVerticalBox* PartyPanelWidget;

	UPROPERTY(BlueprintReadWrite)
	UImage* CrosshairWidget;

	UPROPERTY(BlueprintReadWrite)
	UScoreOverlay* ScorePanelWidget;
};
