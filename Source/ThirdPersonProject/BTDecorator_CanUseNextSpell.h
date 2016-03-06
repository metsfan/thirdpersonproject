// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanUseNextSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UBTDecorator_CanUseNextSpell : public UBTDecorator
{
	GENERATED_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
