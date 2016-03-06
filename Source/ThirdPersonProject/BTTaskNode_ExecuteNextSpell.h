// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_ExecuteNextSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UBTTaskNode_ExecuteNextSpell : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory);
};
