// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTService_ChooseNextSpell.h"
#include "BaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_ChooseNextSpell::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto controller = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	auto blackboard = OwnerComp.GetBlackboardComponent();

	blackboard->SetValueAsClass("NextSpell", controller->GetNextSpell());
}