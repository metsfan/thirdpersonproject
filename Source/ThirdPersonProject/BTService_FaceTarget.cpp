// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BTService_FaceTarget.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTService_FaceTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto owningActor = OwnerComp.GetAIOwner()->GetPawn();
	auto blackboard = OwnerComp.GetBlackboardComponent();
	auto currentTarget = Cast<ACharacter>(blackboard->GetValueAsObject("CurrentTarget"));

	FVector normDirection = (currentTarget->GetActorLocation() - owningActor->GetActorLocation());
	normDirection.Normalize();
	float dProductAngle = FMath::RadiansToDegrees(acos(FVector::DotProduct(owningActor->GetActorForwardVector(), normDirection)));

	OwnerComp.GetAIOwner()->SetControlRotation(FRotator(0, 0, dProductAngle));
}