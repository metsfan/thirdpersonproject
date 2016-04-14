// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "Components/GridPanel.h"
#include "MainGameState.h"
#include "MyPlayerState.h"
#include "Components/TextBlock.h"
#include "ScoreOverlay.generated.h"

/**
 * 
 */

UCLASS()
class THIRDPERSONPROJECT_API UScoreOverlay : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void UpdateScoreTable();

	TArray<AMyPlayerState*> ConnectedPlayers;

protected:
	UPROPERTY(BlueprintReadWrite)
		UGridPanel* GridWidget;

private:
	TArray<UTextBlock*> NameWidgets;
	TArray<UTextBlock*> KillsWidgets;
	TArray<UTextBlock*> AssistsWidgets;
	TArray<UTextBlock*> DamageDoneWidgets;
	TArray<UTextBlock*> DamageTakenWidgets;
};
