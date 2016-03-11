// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BehaviorTree/BlackboardData.h"
#include "BTService_ChooseTarget.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_ChooseTarget::UBTService_ChooseTarget()
{
}

void UBTService_ChooseTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (GetWorld()) {
		PlayerActors.Empty();
		for (TActorIterator<AThirdPersonProjectCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			PlayerActors.Add(*ActorItr);
		}

		auto owningActor = OwnerComp.GetAIOwner()->GetPawn();
		auto blackboard = OwnerComp.GetBlackboardComponent();
		double MinDistance = INFINITY;
		AThirdPersonProjectCharacter* MinDistancePlayer = NULL;

		for (auto player : PlayerActors) {
			if (MinDistancePlayer) {
				double distance = player->GetDistanceTo(owningActor);
				if (distance < MinDistance) {
					MinDistancePlayer = player;
					MinDistance = distance;
				}
			}
			else {
				MinDistancePlayer = player;
			}
		}

		blackboard->SetValueAsObject("CurrentTarget", MinDistancePlayer);
	}
	
}


