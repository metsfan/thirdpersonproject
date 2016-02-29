// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ActionEvent.h"
#include "MainPlayerController.generated.h"


UCLASS(Blueprintable)
class THIRDPERSONPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()


		virtual void BeginPlay();
	
public:

	
protected:
	virtual void SetupInputComponent() override;
};
