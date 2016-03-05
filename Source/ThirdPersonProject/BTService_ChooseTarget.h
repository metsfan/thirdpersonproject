// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "ThirdPersonProjectCharacter.h"
#include "BTService_ChooseTarget.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONPROJECT_API UBTService_ChooseTarget : public UBTService
{
	GENERATED_BODY()

	UBTService_ChooseTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:

	TArray<AThirdPersonProjectCharacter *> PlayerActors;
};
