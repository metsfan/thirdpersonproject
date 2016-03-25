// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTTask_MoveToNextSpellRange.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpellData.h"

EBTNodeResult::Type UBTTask_MoveToNextSpellRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto owningActor = OwnerComp.GetAIOwner()->GetPawn();
	auto blackboard = OwnerComp.GetBlackboardComponent();
	auto spell = Cast<USpellData>(blackboard->GetValueAsObject("NextSpell"));
	if (spell) {
		// Just a bit less than the spell's max range, in case our guy goes just a bit too far
		this->AcceptableRadius = spell->MaxRange * 0.95;
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}