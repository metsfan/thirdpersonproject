// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Controller.h"
#include "BaseMovementController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API ABaseMovementController : public AController
{
	GENERATED_BODY()



	virtual void SetupPlayerInputComponent(UInputComponent* InInputComponent);

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);
};
