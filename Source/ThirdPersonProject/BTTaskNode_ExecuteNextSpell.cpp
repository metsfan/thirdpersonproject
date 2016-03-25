// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTTaskNode_ExecuteNextSpell.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BaseAIController.h"
#include "BaseCharacter.h"
#include "SpellCPP.h"

EBTNodeResult::Type UBTTaskNode_ExecuteNextSpell::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto spell = Cast<USpellData>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("NextSpell"));
	if (spell) {
		auto owningActor = OwnerComp.GetAIOwner()->GetPawn();

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = owningActor;
		spawnParams.Instigator = owningActor;

		FTransform* transform = new FTransform(FVector(75, 0, 0));

		auto actor = Cast<ASpellCPP>(GetWorld()->SpawnActor(spell->Class, transform, spawnParams));
		actor->AttachRootComponentToActor(owningActor);
		actor->Finish();
	}
	return EBTNodeResult::Type::Succeeded;
}


