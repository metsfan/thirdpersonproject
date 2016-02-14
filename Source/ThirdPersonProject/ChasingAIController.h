// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "ChasingAIController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API AChasingAIController : public AAIController
{
	GENERATED_BODY()


		virtual void BeginPlay() override;
	
};
