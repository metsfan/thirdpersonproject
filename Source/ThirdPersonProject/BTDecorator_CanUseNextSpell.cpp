// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTDecorator_CanUseNextSpell.h"
#include "BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

bool UBTDecorator_CanUseNextSpell::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto owningActor = OwnerComp.GetAIOwner()->GetPawn();
	auto blackboard = OwnerComp.GetBlackboardComponent();
	auto spell = blackboard->GetValueAsClass("NextSpell");
	if (spell) {
		auto currentTarget = Cast<ACharacter>(blackboard->GetValueAsObject("CurrentTarget"));

		double distance = owningActor->GetDistanceTo(currentTarget);

		UE_LOG(MyLog, Log, TEXT("Distance to target: %f"), distance)

		return distance < 1500;
	}

	return false;
}


