// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTDecorator_CanUseNextSpell.h"
#include "BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SpellData.h"

bool UBTDecorator_CanUseNextSpell::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto owningActor = OwnerComp.GetAIOwner()->GetPawn();
	auto blackboard = OwnerComp.GetBlackboardComponent();
	auto spell = Cast<USpellData>(blackboard->GetValueAsObject("NextSpell"));
	if (spell) {
		auto currentTarget = Cast<ACharacter>(blackboard->GetValueAsObject("CurrentTarget"));

		double distance = owningActor->GetDistanceTo(currentTarget);

		//UE_LOG(MyLog, Log, TEXT("Distance: %f, Spell Range: %d"), distance, spell->MaxRange);

		return distance < spell->MaxRange;
	}

	return false;
}


