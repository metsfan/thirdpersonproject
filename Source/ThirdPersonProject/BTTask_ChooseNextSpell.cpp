// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTTask_ChooseNextSpell.h"
#include "BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskNode_ChooseNextSpell::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto controller = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	auto blackboard = OwnerComp.GetBlackboardComponent();

	auto spellClass = controller->GetNextSpell();
	auto spellData = NewObject<USpellData>(GetTransientPackage(), spellClass);
	blackboard->SetValueAsObject("NextSpell", spellData);

	return EBTNodeResult::Type::Succeeded;
}