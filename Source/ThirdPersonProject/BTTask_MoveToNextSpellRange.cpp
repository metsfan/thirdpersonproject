// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTTask_MoveToNextSpellRange.h"

EBTNodeResult::Type UBTTask_MoveToNextSpellRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	this->AcceptableRadius = 1000;

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}