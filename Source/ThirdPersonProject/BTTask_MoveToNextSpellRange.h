// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToNextSpellRange.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UBTTask_MoveToNextSpellRange : public UBTTask_MoveTo
{
	GENERATED_BODY()

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
