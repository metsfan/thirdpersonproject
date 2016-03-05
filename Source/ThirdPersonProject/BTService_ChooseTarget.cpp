// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BehaviorTree/BlackboardData.h"
#include "BTService_ChooseTarget.h"

UBTService_ChooseTarget::UBTService_ChooseTarget()
{
}

void UBTService_ChooseTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (GetWorld()) {
		if (PlayerActors.Num() == 0)
		{
			for (TActorIterator<AThirdPersonProjectCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
			{
				PlayerActors.Add(*ActorItr);
			}
		}

		auto blackboard = this->GetBlackboardAsset();
	}
	
}


