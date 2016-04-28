// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTTaskNode_ExecuteNextSpell.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BaseAIController.h"
#include "BaseCharacter.h"
#include "SpellCPP.h"
#include "ProjectileSpell.h"

EBTNodeResult::Type UBTTaskNode_ExecuteNextSpell::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	auto target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("CurrentTarget"));
	if (!target->IsAlive()) {
		return EBTNodeResult::Type::Failed;
	}

	auto spell = Cast<USpellData>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("NextSpell"));
	if (spell) {
		auto owningActor = OwnerComp.GetAIOwner()->GetPawn();

		FSpellSpawnParams params;
		params.Target = target;
		params.TargetLocation = target->GetActorLocation();

		FTransform transform(FVector(75, 0, 0));
		auto actor = spell->SpawnSpell(GetWorld(), owningActor, owningActor, transform, params);
		if (actor) {
			actor->Finish();
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsObject("CurrentTarget", NULL);
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("NextSpell", NULL);
	}
	return EBTNodeResult::Type::Succeeded;
}


