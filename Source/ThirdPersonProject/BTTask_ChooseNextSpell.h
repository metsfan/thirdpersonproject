// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ChooseNextSpell.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UBTTaskNode_ChooseNextSpell : public UBTTaskNode
{
	GENERATED_BODY()
	
	//virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
};
