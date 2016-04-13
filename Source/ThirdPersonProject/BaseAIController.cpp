// Fill out your copyright notice in the Description page of Project Settings.

#include "ThirdPersonProject.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseCharacter.h"
#include "BaseAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Fireball.h"

static ConstructorHelpers::FClassFinder<ASpellCPP>* FireballBPClass = NULL;

ABaseAIController::ABaseAIController(): Super()
{
	if (!FireballBPClass) {
		FireballBPClass = new ConstructorHelpers::FClassFinder<ASpellCPP>(TEXT("/Game/BP_Fireball"));
	}
}

void ABaseAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	auto currentTarget = Cast<ABaseCharacter>(Blackboard->GetValueAsObject("CurrentTarget"));
	if (currentTarget) {
		auto character = Cast<ABaseCharacter>(GetPawn());

		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(character->GetActorLocation(), currentTarget->GetActorLocation());
		rotation.Roll = rotation.Pitch = 0;
		SetControlRotation(rotation);
		//character->CurrentRotation = rotation;
	}
}

TSubclassOf<USpellData> ABaseAIController::GetNextSpell_Implementation()
{
	return NULL;
}


