// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "PlayerFrame.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
	UPlayerFrame* PlayerFrameWidget;
	
};
