// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "SpellData.h"
#include "BaseAIController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

	ABaseAIController();

	virtual void Tick(float deltaSeconds) override;

public:
	UFUNCTION(BlueprintNativeEvent)
		USpellData* GetNextSpell();
	
	virtual USpellData* GetNextSpell_Implementation();
};
