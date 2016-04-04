// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "GameOverHUD.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;
class AMyPlayerState;

enum UGameOverState {
	PlayerAlive,
	PlayerDead,
	ReadyCheck,
	Ready
};

UCLASS()
class THIRDPERSONPROJECT_API UGameOverHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRestartClickSignature);
	FRestartClickSignature OnRestartClick;

	void OnPlayerReady(AMyPlayerState* player);

	void SetState(UGameOverState newState);

	UPROPERTY(BlueprintReadWrite)
	UButton* RestartButtonWidget;

	UPROPERTY(BlueprintReadWrite)
	UTextBlock* GameOverTextWidget;

	//void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateState();

protected:
	void NativeConstruct() override;

private:
	UGameOverState State;

	UFUNCTION()
		void OnRestartClicked();
};
