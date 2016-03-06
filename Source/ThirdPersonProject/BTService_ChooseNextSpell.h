// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "BTService_ChooseNextSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UBTService_ChooseNextSpell : public UBTService
{
	GENERATED_BODY()
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	
};
