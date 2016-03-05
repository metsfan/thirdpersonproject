// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ActionEvent.h"
#include "MainPlayerController.generated.h"


UCLASS(Blueprintable)
class THIRDPERSONPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMainPlayerController();

	virtual void BeginPlay();
	
	virtual void SetPawn(APawn* InPawn) override;
	virtual void Tick(float deltaSeconds) override;
public:

	
protected:
	virtual void SetupInputComponent() override;
};
